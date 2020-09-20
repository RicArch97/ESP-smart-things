/*
Convert string from the cloud to JSON for data extraction.
*/

#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>
#include <vector>

class Json {
public:
    Json(String jsonString);
    ~Json();
    String get(String key);
    String get(int object, String key);
    Json **toArray();
    int size();
private:
    DynamicJsonDocument *doc;
    int objectAmount = 0;
    int keyAmount = 0;
    Json **arr = NULL;
};

#endif