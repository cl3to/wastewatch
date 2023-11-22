#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <ArduinoJson.h>

void init_wifi(const char* ssid, const char* pwd);
void jsonMQTTmsgDATA(const char *device_id, const char *metric, float value, char* output, uint8_t size);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif