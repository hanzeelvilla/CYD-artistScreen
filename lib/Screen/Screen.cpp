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
  tft.drawCentreString("Connecting to Wifi...", X_CENTER_SCREEN, Y_CENTER_SCREEN, NORMAL_TEXT);
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
  tft.drawCentreString(song->name, X_CENTER_SCREEN, Y_CENTER_SCREEN - 60, NORMAL_TEXT);
  tft.setTextSize(1);
  tft.drawCentreString(song->artist, X_CENTER_SCREEN, Y_CENTER_SCREEN, NORMAL_TEXT);
  tft.drawCentreString(song->album, X_CENTER_SCREEN, Y_CENTER_SCREEN + 20, NORMAL_TEXT);
}

void Screen::drawPreviousBtn() {
  tft.fillCircle(X_PREVIOUS_BTN, Y_BTN, RADIUS, TFT_BLUE);
  tft.fillTriangle(
    X_PREVIOUS_BTN - 10, Y_BTN, 
    X_PREVIOUS_BTN + 10, Y_BTN - 10, 
    X_PREVIOUS_BTN + 10, Y_BTN + 10,
    TFT_WHITE
  );
  tft.fillRect(
    X_PREVIOUS_BTN - 12, 
    Y_BTN - 10,
    3,
    20,
    TFT_WHITE
  );
}

void Screen::drawPauseBtn() {
  tft.fillCircle(X_CENTER_SCREEN, Y_BTN, RADIUS, TFT_BLUE); 
  tft.fillRect(
    X_CENTER_SCREEN - 10, 
    Y_BTN - 15,
    5,
    30,
    TFT_WHITE
  );
  tft.fillRect(
    X_CENTER_SCREEN + 5, 
    Y_BTN - 15,
    5,
    30,
    TFT_WHITE
  );
}

void Screen::drawPlayBtn() {
  tft.fillCircle(X_CENTER_SCREEN, Y_BTN, RADIUS, TFT_BLUE); 
  tft.fillTriangle(
    X_CENTER_SCREEN - 10, Y_BTN - 15, 
    X_CENTER_SCREEN - 10, Y_BTN + 15, 
    X_CENTER_SCREEN + 15, Y_BTN,
    TFT_WHITE
  );
}

void Screen::drawNextBtn() {
  tft.fillCircle(X_NEXT_BTN, Y_BTN, RADIUS, TFT_BLUE);
  tft.fillTriangle(
    X_NEXT_BTN + 10, Y_BTN, 
    X_NEXT_BTN - 10, Y_BTN - 10, 
    X_NEXT_BTN - 10, Y_BTN + 10,
    TFT_WHITE
  );
  tft.fillRect(
    X_NEXT_BTN + 9, 
    Y_BTN - 10,
    3,
    20,
    TFT_WHITE
  );
}

void Screen::drawWifiLost() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawCentreString("WiFi connection lost", X_CENTER_SCREEN, Y_CENTER_SCREEN, NORMAL_TEXT);
}