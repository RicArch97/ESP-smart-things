/*
  wifi.cpp - Provides wifi connectivity.
  Created by Ricardo Steijn, September 29, 2020.
*/

#include "wifi.h"

void Wifi::connect(const char* ssid, const char* password) {
    // set mode
    WiFi.mode(WIFI_STA);
    delay(1000);

    // connect to the router
    WiFi.begin(ssid, password);
 
    Serial.print("Connecting to network ");
    Serial.print(ssid);
    Serial.println(". This can take a few seconds.");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Wifi connection successful.");
}

String Wifi::getIP() {
  // return the IP address of the ESP.
  return WiFi.localIP().toString();
}

int32_t Wifi::getRSSI() {
  // return the RSSI (signal strength) from the ESP to the router.
  return WiFi.RSSI();
}