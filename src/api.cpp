/*
The API for the weatherstation.
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
    if (registerStudent == true) 
    obj = new Json(postRequest("register", loginJson, false));
    else if (registerStudent == false)
    obj = new Json(postRequest("login", loginJson, false));

    Serial.println("Login to API successful.");

    String stringId = obj->get("StudentID");
    int id = stringId.toInt();
    this->key = obj->get("Key");
    // free allocated memory
    delete obj;

    return id;
}

int API::postWeatherData(String dataType, double value, int timestamp, int weatherStationId) {
    // post weather data to the cloud, obtained from a sensor.
    // returns weatherDataId.
    DynamicJsonDocument doc(1024);
    doc["DataType"] = dataType;
    doc["Value"] = value;
    doc["Timestamp"] = timestamp;
    doc["WeatherStationID"] = weatherStationId;
    String data;
    serializeJson(doc, data);

    Json obj = Json(postRequest("weatherData", data, true));
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

    Json obj = Json(postRequest("weatherStation", createStation, true));
    String id = obj.get("ID");
    int weatherStationId = id.toInt();

    return weatherStationId;
}

template <typename T>
void API::postEvent(String eventType, T value) {
    // fire an event of any eventType, with any value.
    DynamicJsonDocument doc(1024);
    doc["Event"] = eventType;
    doc["Parameter"] = value;
    String event;
    serializeJson(doc, event);

    postRequest("event", event, true);
}

Json API::getEvents(int weatherStationId) {
    // return all events for a weatherstation.
    return Json(getRequest("event/"+weatherStationId, true));
}

Json API::getWeatherData() {
    // return all data.
    return Json(getRequest("weatherData", false));
}

Json API::getWeatherData(String dataType) {
    // return data for a certain datatype.
    return Json(getRequest("weatherData?DataType="+dataType, false));
}

Json API::getWeatherData(String dataType, int dateTime) {
    // return data for a certain dataType, before a certain date/time.
    return Json(getRequest("weatherData?DataType="+dataType+"&BeforeDateTime"+String(dateTime), false));
}

Json API::getWeatherData(String dataType, int beforeDateTime, int afterDateTime) {
    // return data for a certain dataType, before and after a certain date/time.
    return Json(getRequest("weatherData?DataType="+dataType+"&BeforeDateTime="+String(beforeDateTime)+"&AfterDateTime="+String(afterDateTime), false));
}

Json API::getWeatherStation(int weatherStationId) {
    // get the data for a specific weatherstation.
    return Json(getRequest("weatherStation/"+String(weatherStationId), false));
}

String API::getRequest(String endpoint, bool auth=false) {
    // perform a GET request to the API.
    http.begin(this->client, apiAddress + endpoint);
    http.addHeader("Content-Type", "application/json");
    if (auth == true) http.addHeader("access-key", this->key);

    int returnValue = http.GET();
    if (returnValue != 200) {
        switch (returnValue) {
            case 401: Serial.println("Authentication error");
            break;
            case 404: Serial.println("No data found");
            break;
            case 412: Serial.println("Invalid arguments for request");
            break;
            default: Serial.println("Unknown error occured. Try again.");
            break;
        }
    }
    String response = http.getString();
    http.end();

    return response;
}

String API::postRequest(String endpoint, String json, bool auth) {
    // perform a POST request to the API.
    http.begin(this->client, apiAddress + endpoint);
    http.addHeader("Content-Type", "application/json");
    if (auth == true) http.addHeader("access-key", this->key);

    int returnValue = http.POST(json);
    if (returnValue != 200) {
        switch (returnValue) {
            case 401: Serial.println("Authentication error");
            break;
            case 404: Serial.println("No data found");
            break;
            case 412: Serial.println("Invalid arguments for request");
            break;
            default: Serial.println("Unknown error occured. Try again.");
            break;
        }
    }
    String response = http.getString();
    http.end();

    return response;
}