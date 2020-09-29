/*
  wifi.h - Provides wifi connectivity.
  Created by Ricardo Steijn, September 29, 2020.
*/

#ifndef WIFI_H
#define WIFI_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ESP32
#include <WiFi.h>
#endif

class Wifi{
public:
  void connect(const char* ssid, const char* password);
  String getIP();
  int32_t getRSSI();
};


#endif