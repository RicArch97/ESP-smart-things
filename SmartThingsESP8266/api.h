/*
  api.h - User friendly methods to interact with the Smart Things REST API.
  Created by Ricardo Steijn, September 14, 2020.

  REST API was created by Bart Klomp. https://github.com/imdutch21/weatherstation-api.
*/

#ifndef API_H
#define API_H

#include <ESP8266HTTPClient.h>
#include "json.h"

class API {
public: 
    void postEvent(String eventType, String value);
    int login(String studentId, String password, bool registerStudent);
    int createWeatherStation(String name, double latitude, double longitude);
    int postWeatherData(String dataType, double value, int timestamp, int weatherStationId);
    String getRequest(String endpoint, bool auth);
    String postRequest(String endpoint, String json, bool auth);
    Json getWeatherData();
    Json getWeatherData(String dataType);
    Json getWeatherData(String dataType, int dateTime);
    Json getWeatherData(String dataType, int beforeDateTime, int afterDateTime);
    Json getWeatherStation(int weatherStationId);
    Json getEvents(int weatherStationId);
private:
    HTTPClient http;
    WiFiClient client;
    String key;
};

#endif