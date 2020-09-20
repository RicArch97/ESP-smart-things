/*
The wifi class for connectivity
*/

#include "wifi.h"

void Wifi::connect(const char* ssid, const char* password) {
    // set modes
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);

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

    this->ipAdress = WiFi.localIP();
    this->rssi = WiFi.RSSI();
}