#ifndef MTTT_H
#define MTTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "utils.h"


class MQTTClient {
    public:
        MQTTClient(char* user, char* pwd){
            _user = user;
            _pwd = pwd;
        }

        void setPubTopic(char* pub){
            _pub = pub;
        }

        void setSubTopic(char* sub){
            _sub = sub;
        }

        void publish(char* msg){
            _client.publish(_pub, msg);
        }

        bool connected(){
            return _client.connected();
        }

        bool begin(const char* ssid, const char* pwd, const char* host);
        void reconnect();
    private:
        WiFiClient _wifiClient;
        PubSubClient _client;
        char* _user;
        char* _pwd;
        char* _pub;
        char* _sub;
};

#endif