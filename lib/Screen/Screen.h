#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../spotifyController/spotifyController.h"

/* --------------------------------- SCREEN --------------------------------- */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_X_CENTER SCREEN_WIDTH / 2
#define SCREEN_Y_CENTER SCREEN_HEIGHT / 2

/* ----------------------------------- BTN ---------------------------------- */
#define PREVIOUS_BTN_X_CENTER SCREEN_X_CENTER - 100
#define NEXT_BTN_X_CENTER SCREEN_X_CENTER + 100
#define BTN_RADIUS 30
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
        bool isPreviousBtnPressed(int x, int y);
        bool isNextBtnPressed(int x, int y);
};

#endif