#include "smartThings.h"

Wifi wifi;
API api;
//dht11 dht;

// TODO
// sensor pins
int dht11pin = 8;
//int servo = 9;

// save your important variables here
int weatherStationId;
int studentId;

void setup() {
  Serial.begin(9600);
  // TODO
  // select a mode for your pins (input for sensors, output for actuators)
  pinMode(dht11pin, INPUT);
  //pinMode(servo, OUTPUT);

  // TODO
  // connect to wifi, provide ssid name and password.
  wifi.connect("YourSSID", "YourPassword");
  // login. If you need to register, set registerStudent to true.
  studentId = api.login("YourStudentNumber", "YourPassword", false);
  // studentId = api.login("YourStudentNumber", "YourPassword", true);
  // wait 10s. This is mandatory so the server doesn't get overloaded with requests. The server plan is free :)
  delay(10000);
  /* TODO
    create a weatherstation (ONLY IF YOU DIDN'T CREATE ONE YET!)
    provide latitude and longitude. You can get that info here: https://www.latlong.net/
    this is to show your weatherstation's position on the map.
  */
  weatherStationId = api.createWeatherStation("MyWeatherStation", 1.00, 1.00);
}

void loop() {
  /* TODO 
    Program your sensor here, read values for example.
    dht.read(dht11pin);
    double humidity = dht.humidity;
    double temperature = dht.temperature;
  */
  double humidity, temperature;
  
  // post the sensordata to the server.
  // you can use a DateTime library if realistic timestaps, if you like.
  api.postWeatherData("Humidity", humidity, 20092020, weatherStationId);
  api.postWeatherData("Temperature", temperature, 20092020, weatherStationId);

  /* READ
    this is optional. You can get data as array or specify the object index like so: String value = weatherData.get(2, "Value");
    when using an array, note that a pointer is required to point at the data, as it is saved in the memory. use the arrow instead of "."
    weatherData.toArray()[0]->get("Value");
  */
  Json weatherData = api.getWeatherData();
  for (int i = 0; i < weatherData.size(); i++) {
    Serial.println(weatherData.toArray()[i]->get("DataType"));
  }

  // 10s delay between uploads
  delay(10000);
}