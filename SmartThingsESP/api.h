/*
  api.h - User friendly methods to interact with the Smart Things REST API.
  Created by Ricardo Steijn, September 14, 2020.
  Last edit on September 29, 2020.

  REST API was created by Bart Klomp. https://github.com/imdutch21/weatherstation-api.
*/

#ifndef API_H
#define API_H

#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#endif

#ifdef ESP32
#include <HTTPClient.h>
#endif

#include "json.h"

class API {
public: 
  void postEvent(String eventType, String value, int weatherStationId);
  int login(String studentId, String password, bool registerStudent);
  int createWeatherStation(String name, double latitude, double longitude);
  int postWeatherData(String dataType, double value, int weatherStationId); 
  Json getWeatherData();
  Json getWeatherData(String dataType);
  Json getWeatherData(String dataType, int afterDateTime);
  Json getWeatherData(String dataType, int beforeDateTime, int afterDateTime);
  Json getWeatherStation(int weatherStationId);
  Json getEvents(int weatherStationId);
private:
  String getRequest(String endpoint, bool auth);
  String postRequest(String endpoint, String json, bool auth);
  void raiseError();
  HTTPClient http;
  WiFiClient client;
  String key;
  int returnValue;
};

#endif