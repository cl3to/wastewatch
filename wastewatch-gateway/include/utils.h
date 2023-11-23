#ifndef UTILS_H
#define UTILS_H

#define FORMAT "{\"R\": %s \"P\": %f}"

#include <Arduino.h>
#include <ArduinoJson.h>

void init_wifi(const char* ssid, const char* pwd);
float extract_data(char* buffer, char* restaurant);
void jsonMQTTmsgDATA(const char *device_id, const char *metric, float value, char* output, uint8_t size);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif