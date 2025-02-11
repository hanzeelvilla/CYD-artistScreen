// RENAME THIS FILE TO config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <XPT2046_Touchscreen.h>

#include <Screen.h>
#include <spotifyController.h>

/* ---------------------------------- WIFI ---------------------------------- */
#define SSID1 "your_ssid1"
#define PSWD1 "your_pswd1"
#define SSID2 "your_ssid2"
#define PSWD2 "your_pswd2"
// add more APs if needed
//#define SSID3 "your_ssid3"
//#define PSWD3 "your_pswd3"

/* ---------------------------------- TOUCH --------------------------------- */
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
#define TS_MIN 0
#define TS_MAX 4095

/* ------------------------------- TIME ZONES ------------------------------- */
// soon I will add more time zones
#define GMT_6 -21600 

#endif