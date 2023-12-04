#ifndef MTTT_H
#define MTTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "logging.h"
#include "utils.h"

class MQTTClient {
    public:
        MQTTClient(const char* user, const char* pwd){
            _user = user;
            _pwd = pwd;
        }

        void setLogger(Logger* logger){
            _logger = logger;
        }

        void setPubTopic(const char* pub){
            _pub = (char *) pub;
        }

        void setSubTopic(const char* sub){
            _sub = (char *) sub;
        }

        void publish(char* msg){
            _client.publish(_pub, msg);
        }

        bool connected(){
            return _client.connected();
        }

        void loop(){
            _client.loop();
        }

        bool begin(const char* ssid, const char* pwd, const char* host);
        void reconnect();
    private:
        WiFiClient _wifiClient;
        PubSubClient _client;
        const char* _user;
        const char* _pwd;
        char* _pub;
        char* _sub;
        Logger* _logger;
};

#endif
