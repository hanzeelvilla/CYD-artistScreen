#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include "config.h"

TFT_eSPI tft = TFT_eSPI();

bool wifiConnected();
void initWifi();
void reconnectWifi();
void writeWifiData();

void setup() {
  Serial.begin(115200);
  tft.begin();

  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Connecting to " + String(SSID), X_CENTER, Y_CENTER, NORMAL_TEXT);
  
  initWifi();
}

void loop() {
  if (!wifiConnected())
    reconnectWifi();
  
  delay(1000);
}

bool wifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void initWifi() {
  Serial.print("Connecting to: ");
  Serial.println(SSID);

  WiFi.begin(SSID, PSWD);
  while (!wifiConnected()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  writeWifiData();
}

void reconnectWifi() {
  Serial.println("WiFi connection lost");
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawCentreString("WiFi connection lost", X_CENTER, Y_CENTER - 20, NORMAL_TEXT);

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Reconnecting to " + String(SSID), X_CENTER, Y_CENTER, NORMAL_TEXT);

  initWifi();
}

void writeWifiData() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Connected to " + String(SSID), 0, 0, NORMAL_TEXT);
  tft.drawString("IP address: " + WiFi.localIP().toString(), 0, 20, NORMAL_TEXT);
}