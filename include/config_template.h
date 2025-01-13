// RENAME THIS FILE TO config.h

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>
#include <NTPClient.h>
#include <Preferences.h>

#define SSID "your_ssid"
#define PSWD "your_pswd"

#define CLIENT_ID "your_client_id"
#define CLIENT_SECRET "your_client_secret"

// MEXICO TIME ZONE = GMT-6 = -6 * 3600 = -21600
#define TIME_ZONE -21600 

#define TOKEN_URL "https://accounts.spotify.com/api/token"
#define CURRENTLY_PLAYING_URL "https://api.spotify.com/v1/me/player/currently-playing"

// TOKEN_NAMESPACE
#define TOKEN "spotify_token"
#define TOKEN_KEY "token"

// SCREEN
#define WIDTH 320
#define HEIGHT 240
#define X_CENTER WIDTH / 2
#define Y_CENTER HEIGHT / 2

// TEXT
#define NORMAL_TEXT 2 

#endif