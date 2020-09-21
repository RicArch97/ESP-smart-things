# ESP8266-smart-things

This is a library for the minor "Smart Things" of Hogeschool Rotterdam.

# Features

* Connecting to a wifi network.
* Interaction with the full server REST API using friendly methods.

# Requirements

* ESP8266 development board, for example: NodeMCU ESP-12E.
* Micro USB cable.
* Wifi network (WPA/WPA2 secured), a mobile hotspot works too.

# Usage

## Arduino IDE

* Go to File -> Preferences. Find "Additional Boards Manager URLs" and paste `https://arduino.esp8266.com/stable/package_esp8266com_index.json`. Then go to Tools -> Board: -> Boards manager. Search for "esp8266" and install it.
* Go to Sketch -> Include Library -> Manage Libraries. Search for "ArduinoJson" and install it.
* From this repository, copy the "SmartThingsESP8266" folder into your Arduino library location. For Windows that will be in Documents/Arduino/libraries. For Linux that will be in ~/Arduino/libraries.
* Head over to the "SmartThingsESP8266" folder, go to examples -> SmartThingsExample and change that extenstion on "SmartThingsExample.cpp" to "SmartThingsExample.ino".
* In the Arduino IDE go to File -> Examples -> SmartThingsESP8266 and open "SmartThingsExample".

## Visual Studio Code (recommended)

* Go to extentions, search for PlatformIO, and install it. (skip this step if you already have this)
* Open this entire repo as folder.
* Go to SmartThingsESP8266 -> examples -> SmartThingsExample and open "SmartThingsExample.cpp".
* To build, click the platformIO logo in the sidebar, and click "build". To test your code, click "upload and monitor".

For questions or bugs, message me :)
