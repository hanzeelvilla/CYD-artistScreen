#ifndef SPOTIFYCONTROLLER_H
#define SPOTIFYCONTROLLER_H

#include <HTTPClient.h>
#include <Preferences.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

/* ----------------------------------- URL ---------------------------------- */
#define TOKEN_URL "https://accounts.spotify.com/api/token"
#define CURRENTLY_PLAYING_URL "https://api.spotify.com/v1/me/player/currently-playing"

/* ----------------------------- TOKEN NAMESPACE ---------------------------- */
// This namespace is used to store the token in the ESP32's flash memory, you can change it if you want
#define TOKEN "spotify_token"
#define TOKEN_KEY "token"

struct Song {
    String name;
    String album;
    String artist;
    bool isPlaying;
    unsigned long duration; // in ms
    unsigned long progress; // in ms
};

class SpotifyController {
    private:
        Preferences preferences;
        String getTokenFromNamespace();
        void saveTokenInNamespace(String token);
        String generateToken();
        String token;
    public:
        void init();
        JsonDocument getCurrentSong();
};  

#endif