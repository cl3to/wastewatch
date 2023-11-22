#ifndef LORA_H
#define LORA_H

#define RXD2 16
#define TXD2 17

#define LORA_UART_9600 9600

#include <Arduino.h>
#include <HardwareSerial.h>

static HardwareSerial LoRaSerial(2);

class LoRaUART {
    public:
        void begin(int baudRate = LORA_UART_9600);
        void readMessage(char *buffer, uint8_t n);
        void sendMessage(char *message);
    private:
        char _buffer[256];
        HardwareSerial* _serial = &LoRaSerial;
};

#endif