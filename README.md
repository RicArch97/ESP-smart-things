# ESP-smart-things

This is a library for the minor "Smart Things" of Hogeschool Rotterdam.

# Features

* Connecting to a wifi network.
* Interaction with the full server REST API using friendly methods.

# Requirements

* ESP8266 development board or ESP32 development board. The library should work on most boards, I have only tested it on DoIt ESP32 DevKit V1 (ESP32) and NodeMCU ESP-12E (ESP8266).
* Micro USB cable.
* Wifi network (WPA/WPA2 secured), a mobile hotspot works too.

# Usage

## Arduino IDE

* For ESP8266, go to File -> Preferences. Find "Additional Boards Manager URLs" and paste `https://arduino.esp8266.com/stable/package_esp8266com_index.json`. Then go to Tools -> Board: -> Boards manager. Search for "esp8266" and install it.
* For ESP32, go to File -> Preferences. Find "Additional Boards Manager URLs" and paste `https://dl.espressif.com/dl/package_esp32_index.json` (if you already have a link, separate with a comma). Then go to Tools -> Board: -> Boards manager. Search for "esp32" and install it.
* Go to Sketch -> Include Library -> Manage Libraries. Search for "ArduinoJson" and install it.
* From this repository, copy the "SmartThingsESP" folder into your Arduino library location. For Windows that will be in Documents/Arduino/libraries. For Linux that will be in ~/Arduino/libraries.
* Head over to the "SmartThingsESP" folder, go to examples -> SmartThingsExample and change that extenstion on "SmartThingsExample.cpp" to "SmartThingsExample.ino".
* In the Arduino IDE go to File -> Examples -> SmartThingsESP and open "SmartThingsExample".

## Visual Studio Code (recommended)

* Go to extentions, search for PlatformIO, and install it. (skip this step if you already have this)
* Open this entire repo as folder.
* Go to SmartThingsESP -> examples -> SmartThingsExample and open "SmartThingsExample.cpp".
* In "platformio.ini" select a board (comment one of the "default_envs")
* To build, click the platformIO logo in the sidebar, and click "build" for the right board. To test your code, click "upload and monitor" for the right board.

# Function list

## API

#### int login(String studentID, String password, bool registerStudent)
> Login to the REST API. set registerStudent to `true` to register a new student, set to `false` to just login. This function returns the user id for the current logged in user.

#### int createWeatherStation(String name, double latitude, double longitude)
> Create a new weatherstation for current user. To know the latitude and longitude of your location, go to `https://www.latlong.net`. This function returns the weatherStationId of the new weatherstation.

#### int postWeatherData(String dataType, double value, int weatherStationId)
> Post new sensor data to the API. Valid Data types are: `Humidity` (percentage between 0 and 1), `WindSpeed` (value in m/s greater than or equal to 0), `WindDirection` (value in degrees between 0 and 360, with 0 being north), `Temperature` (value in degrees celsius). This function returns the weatherDataId of the data.

#### void postEvent(String eventType, String value, int weatherStationId)
> Post an event of any kind. The value is provided as string, but can be of any type (e.g. "0.00348").

#### Json getWeatherData()
> Get all weatherData. Note that This function returns the **latest 30** data objects in a Json object holding the data.

#### Json getWeatherData(String dataType)
> Get weatherData for a certain dataType (Humidity, Temperature, WindSpeed, WindDirection). This function returns the **latest 30** data objects in a Json object holding the data.

#### Json getWeatherData(String dataType, int afterDateTime)
> Get weatherdata that has been posted after a certain data/time. The timestamp is Unix and can be retrieved from `https://www.unixtimestamp.com`. This function returns the **latest 30** data objects in a Json object holding the data.

#### Json getWeatherData(String dataType, int beforeDateTime, int afterDateTime)
> Get weatherdata that has been posted before a certain date/time and after a certain date/time. This function returns the **latest 30** data objects in a Json object holding the data.

#### Json getWeatherStation(int weatherStationId)
> Get the data for a specific weatherStation. This will return the name, latitude and longitude of the station.

#### Json getEvents(int weatherStationId)
> Get all events that were posted for this specific weatherStation. Can be useful when working with multiple stations. Events are removed from the cloud once this function is called. This function returns the **latest 30** events in a Json object holding the data. 

## Json

Json objects are returned from `get` functions from the api class.

#### String get(String key)
> Get a value from the Json object for a key. (e.g. `weatherStation.get("Latitude")`). This function returns a String with the value.

#### String get(int object, String key)
> Get a value from an array of Json objects, like the weatherData. `object` is the array index. (e.g. `weatherData.get(0, "Value")`) returns the value for the first object in the array). The function returns a string with the value.

#### Json** toArray()
> When multiple data is returned, it can be converted into an array to loop through all the data. This function returns a pointer that points at multiple objects in memory. Because a pointer is returned use like this: (e.g. `weatherData.toArray()[0]->get("Value")`) or iterate over it using a loop.

## Wifi

#### void connect(const char* ssid, const char* password)
> Connect to a wifi network (WPA/WPA2 secured).

#### String getIP()
> Returns the IP address of the connected device.

#### int32_t getRSSI()
> Returns the RSSI (signal strength from device to router).

## Timer

#### Timer(unsigned long milliseconds)
> Create a new timer. Provide the time in milliseconds.

#### void start()
> Start the timer.

#### void stop()
> Stop the timer. This function will print the ellapsed time on the serial monitor.

#### void restart()
> Restart the timer. Can be called when a timer is not finished yet, or when the timer is done.

#### void set(unsigned long milliseconds)
> Set a new time for your timer.

#### void waitFor()
> Block the processor until the timer has finished. This function is similar to delay().

#### bool done()
> Check if the timer has finished. Can be used in an if statement, to execute code only after the timer has finished. This function returns true when the timer has finished, and false if it's not finished.

#### unsigned long getElapsedTime()
> Get the elapsed time of the timer.


For questions or bugs, message me :)