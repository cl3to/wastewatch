#ifndef LORA_H
#define LORA_H

#define RXD2 26
#define TXD2 25

#define LORA_UART_9600 9600

#include <Arduino.h>
#include <SoftwareSerial.h>

// SoftwareSerial LoRaSerial(26, 25);

class LoRaUART {
    public:
        void begin(int baudRate = LORA_UART_9600);
        void readMessage(char *buffer, uint8_t n);
        void sendMessage(char *message);
    private:
        char _buffer[256];
        SoftwareSerial *_serial;
};

#endif