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

# Function list

## API

#### int login(String studentID, String password, bool registerStudent)
> Login to the REST API. set registerStudent to `true` to register a new student, set to `false` to just login. This function returns the user id for the current logged in user.

#### int createWeatherStation(String name, double latitude, double longitude)
> Create a new weatherstation for current user. To know the latitude and longitude of your location, go to `https://www.latlong.net`. This function returns the weatherStationId of the new weatherstation.

#### int postWeatherData(String dataType, double value, int timestamp, int weatherStationId)
> Post new sensor data to the API. Valid types are: `Humidity` (percentage between 0 and 1), `WindSpeed` (value in m/s greater than or equal to 0), `WindDirection` (value in degrees between 0 and 360, with 0 being north), `Temperature` (value in degrees celsius). This function returns the weatherDataId of the data.

#### void postEvent(String eventType, String value)
> Post an event of any kind. The value is provided as string, but can be of any type (e.g. "0.00348").

#### Json getWeatherData(String dataType, int afterDateTime)
> Get weatherdata that has been posted after a certain data/time. The timestamp is Unix and can be retrieved from `https://www.unixtimestamp.com`. Note that if there is too much data from the period of time, the ESP8266 board might not be able to save it in memory and throw a stack overflow. Use with care. This function return a Json object holding the data.

#### Json getWeatherData(String dataType, int beforeDateTime, int afterDateTime)
> Get weatherdata that has been posted before a certain date/time and after a certain date/time. Note that if there is too much data from the period of time, the ESP8266 board might not be able to save it in memory and throw a stack overflow. Use with care. This function returns a Json object holding the data.

#### Json getWeatherStation(int weatherStationId)
> Get the data for a specific weatherStation. This will return the name, latitude and longitude of the station.

#### Json getEvents(int weatherStationId)
> Get all events that were posted for this specific weatherStation. Can be useful when working with multiple stations. Note that if there are too many events saved in the cloud, the ESP8266 board might not be able to save it in memory and throw a stack overflow. Use with care. Events are removed from the cloud once this function is called. This function returns a Json object holding the data. 

## Json

Json objects are returned from `get` functions from the api class.

#### String get(String key)
> Get a value from the Json object for a key. (e.g. `weatherStation.get("Latitude")`). This function returns a String with the value.

#### String get(int object, String key)
> Get a value from an array of Json objects, like the weatherData. `object` is the array index. (e.g. `weatherData.get(0, "Value")`) returns the value for the first object in the array). The function returns a string with the value.

#### Json** toArray()
> When multiple data is returned, it can be converted into an array to loop through all the data. Note that this function stores the data into the memory, until the Json object destructed. If there's too much data, it can cause a stack overflow, use with care. This function returns a pointer that points at multiple objects in memory. Because a pointer is returned use like this: (e.g. `weatherData.toArray()[0]->get("Value")`) or iterate over it using a loop.

## Wifi

#### void connect(const char* ssid, const char* password)
> Connect to a wifi network (WPA/WPA2 secured).

#### String getIP()
> Returns the IP address of the connected device.

#### int32_t getRSSI()
> Returns the RSSI (signal strength from device to router).

For questions or bugs, message me :)
