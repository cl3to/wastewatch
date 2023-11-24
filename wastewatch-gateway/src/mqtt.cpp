#include "mqtt.h"
#include "utils.h"

bool MQTTClient::begin(const char* ssid, const char* pwd, const char* host) {
  _wifiClient = WiFiClient();
  _client = PubSubClient(_wifiClient);

  init_wifi(ssid, pwd);

  _client.setServer(host, 1883);
  _client.setCallback(mqtt_callback);

  return true;
}

void MQTTClient::reconnect() {
  // Loop until we're reconnected
  while (!_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Tring to connect
    if (_client.connect(_user, _user, _pwd)) {
      Serial.println("connected");
      // Subscribe to the topic
      _client.subscribe(_sub);
    } else {
      Serial.print("Failed! Code rc=");
      Serial.print(_client.state());
      Serial.println(" Try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}