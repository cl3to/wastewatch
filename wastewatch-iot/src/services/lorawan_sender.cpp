#include "lorawan_sender.h"

void LoRaWANDataSender::LoRaWANDataSender()
{
    // Startup all pins and UART
    e32ttl.begin();
    logger->debug(("Start LoRaWAN sender...");
}

void LoRaWANDataSender::sendData(const std::string &data)
{
    // Send message
    ResponseStatus response = e32ttl.sendMessage(data);
    // Check If there is some problem of succesfully send
    logger->debug("Data sending status: " + response.getResponseDescription() + "\n");
}
