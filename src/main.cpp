#include "config.h"

/* -------------------------------- VARIABLES ------------------------------- */
WiFiMulti wifiMulti;

// SCREEN
Screen screen;

// TOUCH
SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);

// SPOTIFY CONTROLLER
SpotifyController spotifyController;

// CLOCK
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedTime;

JsonDocument jsonSong;
Song currentSong;
String previousSongId = "";
unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long remainingSongTime = 0; 

/* -------------------------------- FUNCTIONS ------------------------------- */
bool wifiConnected();
void initWifi();

JsonDocument getCurrentSong();

void setup() {
  Serial.begin(115200);
  /* --------------------------------- SCREEN --------------------------------- */
  screen.init();

  /* --------------------------------- WIFI --------------------------------- */
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(SSID1, PSWD1);
  wifiMulti.addAP(SSID2, PSWD2); // comment or remove this line if you have only one AP
  // add more APs if needed
  
  screen.drawFirstWifiConnection();
  initWifi();
  
  /* ---------------------------------- TOUCH --------------------------------- */
  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(mySpi);
  ts.setRotation(1);
  Serial.println("Touch initialized");

  /* ---------------------------------- CLOCK --------------------------------- */
  timeClient.begin(); 
  timeClient.setTimeOffset(GMT_6); // adjust timezone
  
  /* --------------------------------- SPOTIFY -------------------------------- */
  spotifyController.init();
}

void loop() {
  if (wifiConnected()) {
    Serial.println("Connected to WiFi " + WiFi.SSID());
    
    timeClient.update();
    formattedTime = timeClient.getFormattedTime();
    Serial.println(formattedTime);

    currentTime = millis();
    if (currentTime - previousTime >= COOLDOWN) {
      jsonSong = spotifyController.getCurrentSong();
      
      if (jsonSong.containsKey("item")) {
        currentSong.id = jsonSong["item"]["id"].as<String>();

        if (currentSong.id != previousSongId) {
          previousSongId = currentSong.id;

          currentSong.name = jsonSong["item"]["name"].as<String>();
          currentSong.album = jsonSong["item"]["album"]["name"].as<String>();
          currentSong.artist = jsonSong["item"]["artists"][0]["name"].as<String>();
          currentSong.isPlaying = jsonSong["is_playing"];
          currentSong.duration = jsonSong["item"]["duration_ms"];
          currentSong.progress = jsonSong["progress_ms"];

          screen.clear();
        }
        // else the song is the same
        previousTime = currentTime;
      }
      else { // may be a 429 error or smt else
        currentSong.name = "No song playing";
        currentSong.album = "";
        currentSong.artist = "";
      }
    }

    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      // change cors to screen size
      int touchX = map(p.x, TS_MIN, TS_MAX, 0, SCREEN_WIDTH);
      int touchY = map(p.y, TS_MIN, TS_MAX, 0, SCREEN_HEIGHT);

      Serial.print("X: ");
      Serial.print(touchX);
      Serial.print(" Y: ");
      Serial.println(touchY);
      
      if (screen.isPreviousBtnPressed(touchX, touchY)) {
        Serial.println("Previous button pressed");
        //spotifyController.previous();
      }

      if (screen.isNextBtnPressed(touchX, touchY)) {
        Serial.println("Skippin to next song");
        spotifyController.skipToNextSong();
      }

    }

    if (screen.currentScreen != HOME)
      screen.changeScreen(HOME);
    
  }
  else {
    Serial.println("WiFi connection lost");

    if (screen.currentScreen != WIFI_LOST)
      screen.changeScreen(WIFI_LOST);
  }

  switch (screen.currentScreen) {
    case HOME:
      screen.drawWifiData(WiFi.SSID());
      screen.drawTime(formattedTime);

      if (currentSong.name != "" && currentSong.album != "" && currentSong.artist != "") {
        screen.drawSong(&currentSong);
      }

      screen.drawPauseBtn();
      screen.drawNextBtn();
      screen.drawPreviousBtn();
      break;
    
    case WIFI_LOST:
      screen.drawWifiLost();
      break;
    
  }

  delay(1000);
}

/* -------------------------------- FUNCTIONS ------------------------------- */
bool wifiConnected() {
  return wifiMulti.run() == WL_CONNECTED;
}

void initWifi() {
  Serial.println("Connecting to WiFi...");

  while (!wifiConnected()) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi connected");
  Serial.println("SSID: " + WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  screen.changeScreen(HOME);
}