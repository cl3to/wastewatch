#include <Arduino.h>
#include <cstring>
#include <WiFi.h>
#include "utils.h"

void init_wifi(const char* ssid, const char* pwd, Logger* logger) {
  // WiFi config
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  logger->debug("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    logger->mprint(".");
  }
  logger->mprintln("");
  logger->debug(
    "Connected to WiFi with IP: %s", WiFi.localIP().toString().c_str()
  );
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
