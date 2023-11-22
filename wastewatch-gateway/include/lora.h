#ifndef LORA_H
#define LORA_H

#define RXD2 16
#define TXD2 17

#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial LoRaSerial(2);

class LoRaUART {
    public:
        LoRaUART();
        ~LoRaUART();
        void begin(int baudRate);
        void readMessage(char *buffer, int n);
        void sendMessage(char *message);
    private:
        char _buffer[256];
};

#endif