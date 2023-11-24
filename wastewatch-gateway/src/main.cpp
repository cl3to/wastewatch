#include <Arduino.h>
#include "lora.h"
#include "mqtt.h"
#include "utils.h"
#include "secrets.h"

#define SLEEP_TIME 3000
#define DEBUG_BAUD_RATE 115200

char receiveBuffer[256];

LoRaUART lora;
MQTTClient mqttClient(KONKER_USER, KONKER_PASSWORD);

void setup() {
  // Setup clients
  Serial.begin(DEBUG_BAUD_RATE);
  lora.begin(LORA_UART_9600);
  mqttClient.begin(SSID_NAME, SSID_PASSWORD, MQTT_HOST);
  mqttClient.setPubTopic(MQTT_PUB_TOPIC);
  mqttClient.setSubTopic(MQTT_SUB_TOPIC);
  delay(500);
}

void loop() {

  // Read message from LoRa
  lora.readMessage(receiveBuffer, 30);

  // If the message is not empty, publish it
  if (strlen(receiveBuffer) > 10) {
    Serial.println(receiveBuffer);
    if (!mqttClient.connected()) {
      mqttClient.reconnect();
    }
  
    mqttClient.publish(receiveBuffer);
    mqttClient.loop();
  }

  delay(SLEEP_TIME);
}
