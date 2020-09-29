/*
  json.h - Convert string from the cloud to JSON for data extraction.
  Created by Ricardo Steijn, September 17, 2020.
  Last edit on September 21, 2020.
*/

#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>

class Json {
public:
  Json();
  Json(String jsonString);
  ~Json();
  String get(String key);
  String get(int object, String key);
  Json **toArray();
  int size();
private:
  DynamicJsonDocument *doc = NULL;
  int objectAmount = 0;
  int keyAmount = 0;
  Json **arr = NULL;
};

#endif