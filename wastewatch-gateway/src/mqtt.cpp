#include "mqtt.h"
#include "utils.h"

bool MQTTClient::begin(const char* ssid, const char* pwd, const char* host) {
  _wifiClient = WiFiClient();
  _client = PubSubClient(_wifiClient);

  init_wifi(ssid, pwd, _logger);

  _client.setServer(host, 1883);
  _client.setCallback(mqtt_callback);

  return true;
}

void MQTTClient::reconnect() {
  // Loop until we're reconnected
  while (!_client.connected()) {
    _logger->debug("Attempting MQTT connection...");
    
    // Tring to connect
    if (_client.connect(_user, _user, _pwd)) {
      _logger->debug("connected");
      // Subscribe to the topic
      _client.subscribe(_sub);
    } else {
      _logger->debug("Failed! Code rc=%d Try again in 5 seconds", _client.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}