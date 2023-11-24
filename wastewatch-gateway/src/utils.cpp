#include <Arduino.h>
#include <cstring>
#include <WiFi.h>
#include "utils.h"

void init_wifi(const char* ssid, const char* pwd) {
  // WiFi config
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to WiFi with IP: ");
  Serial.println(WiFi.localIP());
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
