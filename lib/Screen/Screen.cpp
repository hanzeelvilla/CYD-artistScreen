#include "Screen.h"

void Screen::init() {
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    Serial.println("Screen initialized");
}

void Screen::clear() {
  tft.fillScreen(TFT_BLACK);
}

void Screen::changeScreen(myScreens newScreen) {
  currentScreen = newScreen;
  clear();
}

void Screen::drawFirstWifiConnection() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Connecting to Wifi...", SCREEN_X_CENTER, SCREEN_Y_CENTER, NORMAL_TEXT);
}

void Screen::drawWifiData(String ssid) {
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Connected to " + ssid, 0, 0, NORMAL_TEXT);
  //tft.drawString("IP address: " + WiFi.localIP().toString(), 0, 20, NORMAL_TEXT);
}

void Screen::drawTime(String time) {
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString(time, 260, 0, NORMAL_TEXT);
}

void Screen::drawSong(Song *song) {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawCentreString(song->name, SCREEN_X_CENTER, SCREEN_Y_CENTER - 60, NORMAL_TEXT);
  tft.setTextSize(1);
  tft.drawCentreString(song->artist, SCREEN_X_CENTER, SCREEN_Y_CENTER, NORMAL_TEXT);
  tft.drawCentreString(song->album, SCREEN_X_CENTER, SCREEN_Y_CENTER + 20, NORMAL_TEXT);
}

void Screen::drawPreviousBtn() {
  tft.fillCircle(PREVIOUS_BTN_X_CENTER, Y_BTN, BTN_RADIUS, TFT_BLUE);
  tft.fillTriangle(
    PREVIOUS_BTN_X_CENTER - 10, Y_BTN, 
    PREVIOUS_BTN_X_CENTER + 10, Y_BTN - 10, 
    PREVIOUS_BTN_X_CENTER + 10, Y_BTN + 10,
    TFT_WHITE
  );
  tft.fillRect(
    PREVIOUS_BTN_X_CENTER - 12, 
    Y_BTN - 10,
    3,
    20,
    TFT_WHITE
  );
}

void Screen::drawPauseBtn() {
  tft.fillCircle(SCREEN_X_CENTER, Y_BTN, BTN_RADIUS, TFT_BLUE); 
  tft.fillRect(
    SCREEN_X_CENTER - 10, 
    Y_BTN - 15,
    5,
    30,
    TFT_WHITE
  );
  tft.fillRect(
    SCREEN_X_CENTER + 5, 
    Y_BTN - 15,
    5,
    30,
    TFT_WHITE
  );
}

void Screen::drawPlayBtn() {
  tft.fillCircle(SCREEN_X_CENTER, Y_BTN, BTN_RADIUS, TFT_BLUE); 
  tft.fillTriangle(
    SCREEN_X_CENTER - 10, Y_BTN - 15, 
    SCREEN_X_CENTER - 10, Y_BTN + 15, 
    SCREEN_X_CENTER + 15, Y_BTN,
    TFT_WHITE
  );
}

void Screen::drawNextBtn() {
  tft.fillCircle(NEXT_BTN_X_CENTER, Y_BTN, BTN_RADIUS, TFT_BLUE);
  tft.fillTriangle(
    NEXT_BTN_X_CENTER + 10, Y_BTN, 
    NEXT_BTN_X_CENTER - 10, Y_BTN - 10, 
    NEXT_BTN_X_CENTER - 10, Y_BTN + 10,
    TFT_WHITE
  );
  tft.fillRect(
    NEXT_BTN_X_CENTER + 9, 
    Y_BTN - 10,
    3,
    20,
    TFT_WHITE
  );
}

void Screen::drawWifiLost() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawCentreString("WiFi connection lost", SCREEN_X_CENTER, SCREEN_Y_CENTER, NORMAL_TEXT);
}

bool Screen::isPreviousBtnPressed(int x, int y) {
  int dx = x - NEXT_BTN_X_CENTER; // IDK why works this way and not with PREVIOUS_BTN_X_CENTER
  int dy = y - Y_BTN;
  return (dx * dx + dy * dy) <= (BTN_RADIUS * BTN_RADIUS);
}

bool Screen::isNextBtnPressed(int x, int y) {
  int dx = x - PREVIOUS_BTN_X_CENTER; // IDK why works this way and not with NEXT_BTN_X_CENTER 
  int dy = y - Y_BTN;
  return (dx * dx + dy * dy) <= (BTN_RADIUS * BTN_RADIUS);
}