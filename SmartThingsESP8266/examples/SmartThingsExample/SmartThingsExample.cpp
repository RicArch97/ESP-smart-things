/*
  SmartThingsExample.cpp - Example for the Smart Things ESP8266 library.
  Created by Ricardo Steijn, September 20, 2020.
  Last edit on September 22, 2020.
*/

#include <SmartThings.h>

Wifi wifi;
API api;

// TODO
// sensor pins

// save your important variables here
int weatherStationId;
int studentId;

// TODO
// timers
Timer postTimer(20000);  // 20 seconds
Timer getTimer(60000);  // 1 minute

void setup() {
  Serial.begin(115200);
  // TODO
  // select a mode for your pins (input for sensors, output for actuators)
  //pinMode(dht11pin, INPUT); (example)

  // TODO
  // connect to wifi, provide ssid name and password.
  wifi.connect("YourSSID", "YourPassword");
  // login. If you need to register, set registerStudent to true.
  studentId = api.login("YourStudentID", "YourPassword", false);
  // studentId = api.login("YourStudentNumber", "YourPassword", true);
  /* TODO
    create a weatherstation (ONLY IF YOU DIDN'T CREATE ONE YET!)
    provide latitude and longitude. You can get that info here: https://www.latlong.net/
    this is to show your weatherstation's position on the map.
  */
  weatherStationId = api.createWeatherStation("MyWeatherStation", 1.00, 1.00);
  /* TODO
    start your timers here. timers won't block your code, unlike the delay function.
    this means you can still read your sensor data, while your requests won't happen until the timer is done.
    don't start them in the loop, because the start time will be reset every time.
  */
  postTimer.start();
  getTimer.start();
}

void loop() {
  /* TODO 
    Program your sensor here, read values for example.
    dht.read(dht11pin);
    double humidity = dht.humidity;
    double temperature = dht.temperature;
  */
  double humidity = 0, temperature = 0;
  
  // post the sensordata to the server.
  // use the timer to make sure we only post every 20 seconds.
  if (postTimer.done()) {
    Serial.println("Posted weatherData!");
    api.postWeatherData("Humidity", humidity, weatherStationId);
    api.postWeatherData("Temperature", temperature, weatherStationId);
    // restart the timer again (for 20 seconds)
    postTimer.restart();
  }

  // post an event to turn rotate a servo motor.
  // The value is provided as string and can be anything you want.
  // e.g. "180", or "turn on motor".
  // use your own logic using your sensors.
  if (temperature > 25) {
    Serial.println("Posting event");
    api.postEvent("Servo motor", "180", weatherStationId);
  }

  /* READ
    this is optional. You can get data as array or specify the object index like so: String value = events.get(2, "Parameter");
    when using an array, note that a pointer is required to point at the data, as it is saved in the memory. use the arrow instead of "."
    events.toArray()[0]->get("Parameter"), or use a for loop to loop through the events.

    If too many events have built up in the cloud, The ESP might not be able to store the data into the memory after your response is too big.
    When that happens, it will throw a stack overflow and reboot. 
    Note that events are cleared from the database once you use the getEvents method. So try to do that regularly if you happen to send them out a lot.
    Events are useful when working with multiple ESP's, you can send a command to rotate a servo motor for example.
  */
    
  if (getTimer.done()) {
    Serial.println("Got events!");
    Json events = api.getEvents(weatherStationId);
    Json** array = events.toArray();
    for (int i = 0; i < events.size(); i++) {
      Serial.print(array[i]->get("Event"));
      Serial.println(array[i]->get("Parameter"));
    }
    // restart the timer again (for 1 minute)
    getTimer.restart();
  }
}