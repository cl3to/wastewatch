#include <Arduino.h>
#include "lora.h"

void LoRaUART::begin(int baudRate) {
    _serial = new SoftwareSerial(RXD2, TXD2);
    _serial->begin(baudRate);
}

void LoRaUART::readMessage(char *buffer, uint8_t n) {
    int i = 0;
    while (_serial->available() && i < n)
    {
        buffer[i++] = _serial->read();
    }
    buffer[i] = '\0';
}

void LoRaUART::sendMessage(char *message) {
    _serial->println(message);
}
