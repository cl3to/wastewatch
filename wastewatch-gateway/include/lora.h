#ifndef LORA_H
#define LORA_H

#define RXD2 26
#define TXD2 25

#define LORA_UART_9600 9600

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "logging.h"

class LoRaUART {
    public:
        void begin(int baudRate = LORA_UART_9600);
        void readMessage(char *buffer, uint8_t n);
        void sendMessage(char *message);
        void setLogger(Logger *logger) {
            _logger = logger;
        }
    private:
        SoftwareSerial *_serial;
        Logger *_logger;
};

#endif
