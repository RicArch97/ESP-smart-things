/*
  wifi.h - Provides wifi connectivity.
  Created by Ricardo Steijn, September 16, 2020.
*/

#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

class Wifi{
public:
    void connect(const char* ssid, const char* password);
private:
    IPAddress ipAdress;
    int32_t rssi;
};


#endif