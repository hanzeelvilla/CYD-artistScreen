#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>
#include <NTPClient.h>
#include "config.h"

TFT_eSPI tft = TFT_eSPI();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedTime;

String token;

bool wifiConnected();
void initWifi();
void reconnectWifi();
void writeWifiData();
String getToken();

void setup() {
  Serial.begin(115200);
  tft.begin();

  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("Connecting to " + String(SSID), X_CENTER, Y_CENTER, NORMAL_TEXT);
  
  initWifi();
  timeClient.begin();
  timeClient.setTimeOffset(TIME_ZONE);

  token = getToken();
  //Serial.println(token);
}

void loop() {
  if (!wifiConnected())
    reconnectWifi();
  
  timeClient.update();
  formattedTime = timeClient.getFormattedTime();
  //Serial.println(formattedTime);

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString(formattedTime, 260, 0, NORMAL_TEXT);

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

String getToken() {
  HTTPClient http;

  http.begin(TOKEN_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "grant_type=client_credentials&client_id=" + String(CLIENT_ID) + "&client_secret=" + String(CLIENT_SECRET);

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