#include "config.h"

/* -------------------------------- VARIABLES ------------------------------- */
// SCREEN
TFT_eSPI tft = TFT_eSPI();
enum Screen {
  FIRST_WIFI_CONNECTION,
  HOME,
  WIFI_LOST,
};

WiFiMulti wifiMulti;

// CLOCK
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedTime;

Preferences preferences;
String token;

// song
JsonDocument currentSong;

Screen currentScreen = FIRST_WIFI_CONNECTION;

/* -------------------------------- FUNCTIONS ------------------------------- */
bool wifiConnected();
void initWifi();

void changeScreen(Screen newScreen);
void writeFirstWifiConnection();
void writeWifiData();
void writeWifiLost();

String generateToken();
void saveTokenInNamespace(String token);
String getTokenFromNamespace();

JsonDocument getCurrentSong();

void setup() {
  Serial.begin(115200);
  
  /* --------------------------------- SCREEN --------------------------------- */
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  
  /* --------------------------------- WIFI --------------------------------- */
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(SSID1, PSWD1);
  wifiMulti.addAP(SSID2, PSWD2); // comment or remove this line if you have only one AP
  // add more APs if needed
  writeFirstWifiConnection();
  initWifi();
  
  /*
  timeClient.begin();
  timeClient.setTimeOffset(GMT-6); // adjust timezone
  
  // getting token
  token = getTokenFromNamespace();

  if (token == "") { // If the token namespace is empty, generate a new one (first time)
    Serial.println("Token not found, generating a new one");
    
    String newToken = generateToken();
    saveTokenInNamespace(newToken);

    token = getTokenFromNamespace();
    Serial.println("Token generated and saved!");
  }
  else
    Serial.println("A token was found!");

  Serial.println(token);
  */
}

void loop() {
  if (wifiConnected()) {
    Serial.println("Connected to WiFi " + WiFi.SSID());

    if (currentScreen == WIFI_LOST)
      changeScreen(HOME);
  }
  else {
    Serial.println("WiFi connection lost");

    if (currentScreen == HOME)
      changeScreen(WIFI_LOST);
  }

  switch (currentScreen) {
    case HOME:
      writeWifiData();
      break;
    case WIFI_LOST:
      writeWifiLost();
      break;
  }
  
  /*
  if (!wifiConnected())
    reconnectWifi();
  
  timeClient.update();
  formattedTime = timeClient.getFormattedTime();
  //Serial.println(formattedTime);

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString(formattedTime, 260, 0, NORMAL_TEXT);

  */
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

  changeScreen(HOME);
}

void changeScreen(Screen newScreen) {
  currentScreen = newScreen;
  tft.fillScreen(TFT_BLACK);
}

void writeFirstWifiConnection() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Connecting to Wifi...", X_CENTER, Y_CENTER, NORMAL_TEXT);
}

void writeWifiData() {
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Connected to " + WiFi.SSID(), 0, 0, NORMAL_TEXT);
  //tft.drawString("IP address: " + WiFi.localIP().toString(), 0, 20, NORMAL_TEXT);
}

void writeWifiLost() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawCentreString("WiFi connection lost", X_CENTER, Y_CENTER, NORMAL_TEXT);
}

/*
String generateToken() {
  HTTPClient http;

  http.begin(TOKEN_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "grant_type=refresh_token&refresh_token=" + String(SPOTIFY_REFRESH_TOKEN) + "&client_id=" + String(CLIENT_ID) + "&client_secret=" + String(CLIENT_SECRET);

  int httpCode = http.POST(postData);
  String payload = http.getString();
  http.end();

  Serial.println(httpCode);
  Serial.println(payload);

  if (httpCode == 200) {
    JsonDocument doc;
    deserializeJson(doc, payload);
    return doc["access_token"];
  }
  else {
    Serial.println("Failed to get token");
    return "";
  }
}

void saveTokenInNamespace(String token) {
  preferences.begin(TOKEN, false);
  preferences.putString(TOKEN_KEY, token);
  preferences.end();
}

String getTokenFromNamespace() {
  preferences.begin(TOKEN, true);
  String token = preferences.getString(TOKEN_KEY, "");
  preferences.end();

  return token;
}

JsonDocument getCurrentSong() {
  HTTPClient http;

  Serial.println("Fetching current song");
  http.begin(CURRENTLY_PLAYING_URL);
  http.addHeader("Authorization", "Bearer " + token);

  int httpCode = http.GET();
  String payload = http.getString();
  http.end();

  Serial.println(httpCode);
  Serial.println(payload);

  switch (httpCode) {
    case 200:
    {
      JsonDocument doc;
      deserializeJson(doc, payload);
      return doc;
    }
    case 401:
    {
      Serial.println("Token expired, generating a new one");

      String newToken = generateToken();
      saveTokenInNamespace(newToken);
      token = getTokenFromNamespace();

      Serial.println("Token generated and saved!");
      Serial.println(token);
      return getCurrentSong();
    }
    default:
    {
      Serial.println("Failed to get current song");
      JsonDocument doc;
      deserializeJson(doc, payload);
      return doc;
    }
  }
}
*/