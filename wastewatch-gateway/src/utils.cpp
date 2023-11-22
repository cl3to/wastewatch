#include <Arduino.h>
#include <WiFi.h>
#include "utils.h"

void init_wifi(const char* ssid, const char* pwd) {
  // WiFi config
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}


void jsonMQTTmsgDATA(const char *device_id, const char *metric, float value, char* output, uint8_t size) {
	const int capacity = JSON_OBJECT_SIZE(3);
	StaticJsonDocument<capacity> jsonMSG;
	jsonMSG["deviceId"] = device_id;
	jsonMSG["metric"] = metric;
	jsonMSG["value"] = value;
	serializeJson(jsonMSG, output, size);
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
