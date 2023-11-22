// #include <Arduino.h>
// #include <HardwareSerial.h>
#include "lora.h"
#include <WiFi.h>
#include "mqtt.h"
#include "utils.h"

// #define RXD2 16
// #define TXD2 17

#ifndef SSID_NAME
#define SSID_NAME "WasteWatch"
#endif
#ifndef SSID_PASSWORD
#define SSID_PASSWORD "wastewatch"
#endif

// HardwareSerial LoRaSerial(2);


void readMessage(char *buffer, int n) {
  int i = 0;
  while (LoRaSerial.available() && i < n)
  {
    buffer[i++] = LoRaSerial.read();
  }
  buffer[i] = '\0';
}

char receiveBuffer[256];

void setup() {
  // Serial config
  Serial.begin(115200);
  LoRaSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(500);

  // WiFi config
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  readMessage(receiveBuffer, 256);
  Serial.println(receiveBuffer);
  delay(3000);
}
