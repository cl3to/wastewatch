#ifndef UTILS_H
#define UTILS_H

void init_wifi(const char* ssid, const char* pwd);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
