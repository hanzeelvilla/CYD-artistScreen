#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../spotifyController/spotifyController.h"

/* --------------------------------- SCREEN --------------------------------- */
#define WIDTH 320
#define HEIGHT 240
#define X_CENTER_SCREEN WIDTH / 2
#define Y_CENTER_SCREEN HEIGHT / 2

/* ----------------------------------- BTN ---------------------------------- */
#define X_PREVIOUS_BTN X_CENTER_SCREEN - 100
#define X_NEXT_BTN X_CENTER_SCREEN + 100
#define RADIUS 30
#define Y_BTN 200

/* -------------------------------- FONT TEXT ------------------------------- */
#define NORMAL_TEXT 2

enum myScreens {
    FIRST_WIFI_CONNECTION,
    HOME,
    WIFI_LOST
};

class Screen {
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSPI_Button btnPausePlay;
        TFT_eSPI_Button btnNext;
        TFT_eSPI_Button btnPrevious;
    public:
        myScreens currentScreen = FIRST_WIFI_CONNECTION;
        void init();
        void clear();
        void changeScreen(myScreens newScreen);
        void drawFirstWifiConnection();
        void drawWifiData(String ssid);
        void drawTime(String time);
        void drawSong(Song *song);
        void drawPreviousBtn();
        void drawPauseBtn();
        void drawPlayBtn();
        void drawNextBtn();
        void drawWifiLost();
};

#endif