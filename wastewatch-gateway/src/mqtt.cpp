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
  // Entra no Loop ate estar conectado
  while (!_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Usando um ID unico (Nota: IDs iguais causam desconexao no Mosquito)
    // Tentando conectar
    if (_client.connect(_user, _user, _pwd)) {
      Serial.println("connected");
      // Subscrevendo no topico esperado
      _client.subscribe(_sub);
    } else {
      Serial.print("Falhou! Codigo rc=");
      Serial.print(_client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      // Esperando 5 segundos para tentar novamente
      delay(5000);
    }
  }
}