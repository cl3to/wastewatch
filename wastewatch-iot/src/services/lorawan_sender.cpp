#include "lorawan_sender.h"

void LoRaWANDataSender::LoRaWANDataSender()
{
    // Startup serial
    // TODO: Add constantes for this values
    Serial.begin(9600);
    delay(500);

    // Startup all pins and UART
    e32ttl.begin();
    // TODO: Replace to the logger
    Serial.println("Start LoRaWAN sender...");
}

void LoRaWANDataSender::sendData(const std::string &data)
{
    // Send message
    ResponseStatus response = e32ttl.sendMessage(data);
    // Check If there is some problem of succesfully send
    // TODO: Replace to the logger
    Serial.println("Data sending status: " + response.getResponseDescription() + "\n");
}
