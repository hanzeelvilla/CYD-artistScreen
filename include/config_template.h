// RENAME THIS FILE TO config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <NTPClient.h>
#include <Screen.h>

/* ---------------------------------- WIFI ---------------------------------- */
#define SSID1 "your_ssid1"
#define PSWD1 "your_pswd1"
#define SSID2 "your_ssid2"
#define PSWD2 "your_pswd2"
// add more APs if needed
//#define SSID3 "your_ssid3"
//#define PSWD3 "your_pswd3"

/* --------------------------- SPOTIFY CREDENTIALS -------------------------- */
#define CLIENT_ID "your_client_id"
#define CLIENT_SECRET "your_client_secret"
#define SPOTIFY_REFRESH_TOKEN "your_spotify_refresh_token" // with authorization to get the currently playing song

/* ----------------------------------- URL ---------------------------------- */
#define TOKEN_URL "https://accounts.spotify.com/api/token"
#define CURRENTLY_PLAYING_URL "https://api.spotify.com/v1/me/player/currently-playing"

/* ----------------------------- TOKEN_NAMESPACE ---------------------------- */
// you can change these to whatever you want
#define TOKEN "spotify_token"
#define TOKEN_KEY "token"

/* ------------------------------- TIME ZONES ------------------------------- */
// soon I will add more time zones
#define GMT_6 -21600 

#endif