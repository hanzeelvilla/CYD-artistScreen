#include "spotifyController.h"

void SpotifyController::init() {
    token = getTokenFromNamespace();

    if (token == "") { // If the token namespace is empty, generate a new one (first time)
        Serial.println("Token not found, generating a new one");
        
        String newToken = generateToken();
        saveTokenInNamespace(newToken);

        token = getTokenFromNamespace();
        Serial.println("Token generated and saved!");
    }
    else
        Serial.println("A token was found!");

    Serial.println(token);
}

String SpotifyController::getTokenFromNamespace() {
    preferences.begin(TOKEN, true); // read-only
    String token = preferences.getString(TOKEN_KEY, "");
    preferences.end();

    return token;
}

void SpotifyController::saveTokenInNamespace(String token) {
  preferences.begin(TOKEN, false);
  preferences.putString(TOKEN_KEY, token);
  preferences.end();
}

String SpotifyController::generateToken() {
  HTTPClient http;

  http.begin(TOKEN_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "grant_type=refresh_token&refresh_token=" + String(SPOTIFY_REFRESH_TOKEN) + "&client_id=" + String(CLIENT_ID) + "&client_secret=" + String(CLIENT_SECRET);

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

JsonDocument SpotifyController::getCurrentSong() {
  Serial.println("Fetching current song");
  http.begin(CURRENTLY_PLAYING_URL);
  http.addHeader("Authorization", "Bearer " + token);

  int httpCode = http.GET();
  String payload = http.getString();
  http.end();

  Serial.println(httpCode);
  Serial.println(payload);

  switch (httpCode) {
    case 200:
    {
      JsonDocument doc;
      deserializeJson(doc, payload);
      return doc;
    }
    case 401:
    {
      Serial.println("Token expired, generating a new one");

      String newToken = generateToken();
      saveTokenInNamespace(newToken);
      token = getTokenFromNamespace();

      Serial.println("Token generated and saved!");
      Serial.println(token);
      return getCurrentSong();
    }
    default:
    {
      Serial.println("Failed to get current song");
      JsonDocument doc;
      deserializeJson(doc, payload);
      return doc;
    }
  }
}

void SpotifyController::skipToNextSong() {
  http.begin("https://api.spotify.com/v1/me/player/next");
  http.addHeader("Authorization", "Bearer " + token);

  int httpCode = http.POST("");
  String payload = http.getString();
  http.end();

  Serial.println(httpCode);
  Serial.println(payload);
}