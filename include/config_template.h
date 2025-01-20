// RENAME THIS FILE TO config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <NTPClient.h>
#include <Preferences.h>

/* ---------------------------------- WIFI ---------------------------------- */
#define SSID1 "your_ssid1"
#define PSWD1 "your_pswd1"
#define SSID2 "your_ssid2"
#define PSWD2 "your_pswd2"

/* --------------------------- SPOTIFY CREDENTIALS -------------------------- */
#define CLIENT_ID "your_client_id"
#define CLIENT_SECRET "your_client_secret"
#define SPOTIFY_REFRESH_TOKEN "your_spotify_refresh_token"

/* ----------------------------------- URL ---------------------------------- */
#define TOKEN_URL "https://accounts.spotify.com/api/token"
#define CURRENTLY_PLAYING_URL "https://api.spotify.com/v1/me/player/currently-playing"

/* ------------------------------- TIME ZONES ------------------------------- */
#define GMT-6 -21600 

/* ----------------------------- TOKEN_NAMESPACE ---------------------------- */
#define TOKEN "spotify_token"
#define TOKEN_KEY "token"

/* --------------------------------- SCREEN --------------------------------- */
#define WIDTH 320
#define HEIGHT 240
#define X_CENTER WIDTH / 2
#define Y_CENTER HEIGHT / 2

/* -------------------------------- FONT TEXT ------------------------------- */
#define NORMAL_TEXT 2 

#endif