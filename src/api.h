/*
The API class for the weatherstation.
*/
#ifndef API_H
#define API_H

#include <ESP8266HTTPClient.h>
#include "json.h"

class API {
public: 
    template <typename T>
    void postEvent(String eventType, T value);
    int login(String studentId, String password, bool registerStudent);
    int createWeatherStation(String name, double latitude, double longitude);
    int postWeatherData(String dataType, double value, int timestamp, int weatherStationId);
    String getRequest(String endpoint, bool auth);
    String postRequest(String endpoint, String json, bool auth);
    Json getWeatherData(String dataType);
    Json getWeatherData(String dataType, int dateTime);
    Json getWeatherData(String dataType, int beforeDateTime, int afterDateTime);
    Json getWeatherStation(int weatherStationId);
    Json getWeatherData();
    Json getEvents(int weatherStationId);
private:
    HTTPClient http;
    WiFiClient client;
    String key;
};

#endif