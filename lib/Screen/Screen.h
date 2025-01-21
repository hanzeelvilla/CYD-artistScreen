#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

/* --------------------------------- SCREEN --------------------------------- */
#define WIDTH 320
#define HEIGHT 240
#define X_CENTER WIDTH / 2
#define Y_CENTER HEIGHT / 2

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
    public:
        myScreens currentScreen = FIRST_WIFI_CONNECTION;
        void init();
        void changeScreen(myScreens newScreen);
        void writeFirstWifiConnection();
        void writeWifiData(String ssid);
        void writeTime(String time);
        void writeWifiLost();
};

#endif