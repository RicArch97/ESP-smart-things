/*
  json.cpp - Convert string from the cloud to JSON for data extraction.
  Created by Ricardo Steijn, September 19, 2020.
  Last edit on September 22, 2020.
*/

#include "json.h"

Json::Json() {}

Json::Json(String jsonString) {
    size_t capacity;

    // String contains a list of json.
    if (jsonString[0] == '[') {
        // empty array
        if (jsonString[1] == ']') {
            return;
        }
        int keys = 0;
        int objects = 0;
        for (unsigned int i = 0; i < jsonString.length(); i++) {
            // count key/value before comma, in case an extra comma is used after this last value, ignore that.
            // Ignore that comma used between objects for the key count.
            if (jsonString[i] == ',' && jsonString[i + 1] != '}' && jsonString[i + 1] != '{') {
                keys++;
            }
            // Count object before "}," ignore in case an extra comma is placed after the last object in the list.
            if ((jsonString[i] == '}' && jsonString[i + 1] == ',') || 
            (jsonString[i] == '}' && jsonString[i + 2] == ']') || 
            (jsonString[i] == '}' && jsonString[i + 1] == ']')) {
                objects++;
            }
        }
        keys = keys / objects;
        capacity = JSON_ARRAY_SIZE(objects) + objects*JSON_OBJECT_SIZE(keys) + jsonString.length();
        this->objectAmount = objects;
        this->keyAmount = keys;
    }
    else {
        int keys = 0;
        for(unsigned int i = 0; i < jsonString.length(); i++) {
            // count key/value before comma, in case an extra comma is used after the last value, ignore that.
            if (jsonString[i] == ',' && jsonString[i + 1] != '}') {
                keys++;
            }
        }
        capacity = JSON_OBJECT_SIZE(keys) + jsonString.length();
        this->keyAmount = keys;
    }

    // save the json document in memory.
    this->doc = new DynamicJsonDocument(capacity);
    deserializeJson(*this->doc, jsonString);
}

Json::~Json() {
    // free objects in memory when object is removed
    if (this->doc != NULL) delete this->doc;
    if (this->arr != NULL) {
        for (int i = 0; i < this->objectAmount; i++) {
            delete this->arr[i];
        }
        delete[] this->arr;
    }
}

String Json::get(String key) {
    // Json contains list, but only has 1 object.
    // Check for empty class.
    if (this->doc == NULL) return String();

    // check if this method was called on an array of JSON, else return empty string.
    if (this->objectAmount == 1) return get(0, key);
    else if (this->objectAmount > 1) {
        Serial.println("Object not specified. Json contains multiple items.");
        return String();
    }

    JsonVariant var = this->doc->getMember(key);
    String value = var.as<String>();

    return value;
}

String Json::get(int object, String key) {
    // this function is to get data from an object in a list of json.
    // Check for empty class.
    if (this->doc == NULL) return String();

    // get the object and key
    JsonObject obj = this->doc->getElement(object);
    JsonVariant var = obj.getMember(key);
    String value = var.as<String>();

    return value;
}

Json **Json::toArray() {
    // return an array with json objects.
    // note that this will take up extra memory.
    // Check for empty class.
    if (this->doc == NULL) return NULL;

    // using the value of existing pointer.
    DynamicJsonDocument temp = *this->doc;
    JsonArray jsonArr = temp.as<JsonArray>();

    // allocate the required space.
    this->arr = new Json*[this->objectAmount];
    int counter = 0;

    // loop through all objects in the array.
    // create new Json objects using the string of each object.
    for(JsonObject obj : jsonArr) {
        String jsString;
        serializeJson(obj, jsString);
        this->arr[counter] = new Json(jsString);
        counter++;
    }
    
    // return a pointer to the array
    return this->arr;
}

int Json::size() {
    // return the size of the object, if a list of json is provided.
    return this->objectAmount;
}