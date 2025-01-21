#include "Screen.h"

void Screen::init() {
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    Serial.println("Screen initialized");
}

void Screen::changeScreen(myScreens newScreen) {
  currentScreen = newScreen;
  tft.fillScreen(TFT_BLACK);
}

void Screen::writeFirstWifiConnection() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Connecting to Wifi...", X_CENTER, Y_CENTER, NORMAL_TEXT);
}

void Screen::writeWifiData(String ssid) {
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString("Connected to " + ssid, 0, 0, NORMAL_TEXT);
  //tft.drawString("IP address: " + WiFi.localIP().toString(), 0, 20, NORMAL_TEXT);
}

void Screen::writeTime(String time) {
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString(time, 260, 0, NORMAL_TEXT);
}

void Screen::writeWifiLost() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawCentreString("WiFi connection lost", X_CENTER, Y_CENTER, NORMAL_TEXT);
}