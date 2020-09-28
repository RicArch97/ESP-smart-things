/*
  api.cpp - User friendly methods to interact with the Smart Things REST API.
  Created by Ricardo Steijn, September 14, 2020.
  Last edit on September 28, 2020.

  REST API was created by Bart Klomp. https://github.com/imdutch21/weatherstation-api.
*/

#include "api.h"

String apiAddress = "http://smartthings-weatherstations.herokuapp.com/api/";

int API::login(String studentId, String password, bool registerStudent) {
    // login for existing users.
    DynamicJsonDocument doc(1024);
    doc["StudentCode"] = studentId;
    doc["Password"] = password;
    String loginJson;
    serializeJson(doc, loginJson);

    Json *obj;
    if (registerStudent == true) {
        obj = new Json(postRequest("register", loginJson, false));
        if (this->returnValue != 200) {
            switch (this->returnValue) {
                case -1: 
                    Serial.println("Could not connect to the server. Check your connection and try again.");
                    delete obj;
                    return -1;
                case 412: 
                    Serial.println("Student already registered. Logging in using the same credentials...");
                    registerStudent = false;
                    break;
                default: 
                    Serial.println("Unknown error occured.");
                    delete obj;
                    return -1;
            }
        }
    }
    if (registerStudent == false) {
        obj = new Json(postRequest("login", loginJson, false));
        if (this->returnValue != 200) {
            switch (this->returnValue) {
                case -1: 
                    Serial.println("Could not connect to the server. Check your connection and try again.");
                    delete obj;
                    return -1;
                case 401: 
                    Serial.println("Invalid studentID or password.");
                    delete obj;
                    return -1;
                default: 
                    Serial.println("Unknown error occured.");
                    delete obj;
                    return -1;
            }
        }
    }
    
    Serial.println("Login to API successful.");

    String stringId = obj->get("ID");
    int id = stringId.toInt();
    this->key = obj->get("Key");
    // free allocated memory
    delete obj;

    return id;
}

int API::postWeatherData(String dataType, double value, int weatherStationId) {
    // post weather data to the cloud, obtained from a sensor.
    // returns weatherDataId.
    DynamicJsonDocument doc(1024);
    doc["DataType"] = dataType;
    doc["Value"] = value;
    doc["WeatherStationID"] = weatherStationId;
    String data;
    serializeJson(doc, data);

    String response = postRequest("weatherData", data, true);
    if (this->returnValue != 200) {
        raiseError();
        return -1;
    }
    Json obj = Json(response);

    String id = obj.get("ID");
    int weatherDataId = id.toInt();

    return weatherDataId;
}

int API::createWeatherStation(String name, double latitude, double longitude) {
    // create a new weatherstation.
    // returns weatherStationId.
    DynamicJsonDocument doc(1024);
    doc["Latitude"] = latitude;
    doc["Longitude"] = longitude;
    doc["StationName"] = name;
    String createStation;
    serializeJson(doc, createStation);

    String response = postRequest("weatherStation", createStation, true);
    if (this->returnValue != 200) {
        raiseError();
        return -1;
    }
    Json obj = Json(response);

    String id = obj.get("ID");
    int weatherStationId = id.toInt();

    return weatherStationId;
}

void API::postEvent(String eventType, String value, int weatherStationId) {
    // fire an event of any eventType, supply value in a string.
    DynamicJsonDocument doc(1024);
    doc["Event"] = eventType;
    doc["Parameter"] = value;
    doc["WeatherStationID"] = weatherStationId;
    String event;
    serializeJson(doc, event);

    postRequest("event", event, true);
    if (this->returnValue != 200) {
        raiseError();
    }
}

Json API::getEvents(int weatherStationId) {
    // return all events for a weatherstation.
    String response = getRequest("event/"+String(weatherStationId)+"?Limit=30", true);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

Json API::getWeatherData() {
    // return all data.
    String response = getRequest("weatherData?Limit=30", false);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

Json API::getWeatherData(String dataType) {
    // return data for a certain datatype.
    String response = getRequest("weatherData?DataType="+dataType+"&Limit=30", false);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

Json API::getWeatherData(String dataType, int afterDateTime) {
    // return data for a certain dataType, after a certain date/time.
    String response = getRequest("weatherData?DataType="+dataType+"&AfterDateTime="+String(afterDateTime)+"&Limit=30", false);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

Json API::getWeatherData(String dataType, int beforeDateTime, int afterDateTime) {
    // return data for a certain dataType, before and after a certain date/time.
    String response = getRequest("weatherData?DataType="+dataType+"&BeforeDateTime="+String(beforeDateTime)+"&AfterDateTime="+String(afterDateTime)+"&Limit=30", false);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

Json API::getWeatherStation(int weatherStationId) {
    // get the data for a specific weatherstation.
    String response = getRequest("weatherStation/"+String(weatherStationId), false);
    if (this->returnValue != 200) {
        raiseError();
        return Json();
    }
    return Json(response);
}

String API::getRequest(String endpoint, bool auth) {
    // perform a GET request to the API.
    http.begin(this->client, apiAddress + endpoint);
    http.addHeader("Content-Type", "application/json");
    if (auth == true) http.addHeader("access-key", this->key);

    this-> returnValue = http.GET();
    String response = http.getString();
    http.end();

    return response;
}

String API::postRequest(String endpoint, String json, bool auth) {
    // perform a POST request to the API.
    http.begin(this->client, apiAddress + endpoint);
    http.addHeader("Content-Type", "application/json");
    if (auth == true) http.addHeader("access-key", this->key);

    this->returnValue = http.POST(json);
    String response = http.getString();
    http.end();

    return response;
}

void API::raiseError() {
    // check returnvalue and print error messages
    switch (this->returnValue) {
        case -1: 
            Serial.println("Could not connect to the server. Check your connection and try again.");
            break;
        case 401:
            Serial.println("No access key available. Use api.login() to login.");
            break;
        case 404:
            Serial.println("Requested data was not found in the database.");
            break;
        case 412: 
            Serial.println("Some of the provided arguments are incorrect.");
            break;
        default: 
            Serial.println("Unknown error occured.");
            break;
    }
}