#ifndef UTILS_H
#define UTILS_H

#include "logging.h"

void init_wifi(const char* ssid, const char* pwd, Logger* logger);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
