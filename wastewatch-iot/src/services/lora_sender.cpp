#include <Arduino.h>
#include "lora_sender.h"
#include <cstring>

// TODO: Ajust the correct pins for the boards
#ifdef NODEMCU_DEV
#include <SoftwareSerial.h>
SoftwareSerial LoraSerial(D3, D2); // SoftwareSerial Serial(ESPTX, ESPRX)
#endif

#ifdef ESP32_DEV
#include <HardwareSerial.h>
HardwareSerial LoraSerial(2); //Use UART2
#endif

LoraDataSender::LoraDataSender(Logger *logger) {
    this->logger = logger;

    // Startup all pins and UART
    // TODO: Implement more robust initialization
    LoraSerial.begin(9600);
}

void LoraDataSender::sendData(char* data)
{
    // Send message
    // TODO: Improve the implementation
    int written_bytes = LoraSerial.write(data);

    if (written_bytes == (int) strlen(data)) {
        logger->debug("MESSAGE SENT: %s", data);
    } else {
        logger->debug("MESSAGE NOT SENT: %s", data);
    }
}
