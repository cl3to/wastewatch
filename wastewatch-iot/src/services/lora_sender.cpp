#include "lora_sender.h"


// TODO: Ajust the correct pins for the boards
#ifdef NODEMCU_DEV
LoRa_E32 e32ttl(D2, D3); // e32 TX e32 RX NodeMCU
#endif
#ifdef ESP32_DEV
LoRa_E32 e32ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1 ESP32
#endif

LoraDataSender::LoraDataSender(Logger *logger) {
    this->logger = logger;

    // Startup all pins and UART
    e32ttl.begin();
}

void LoraDataSender::sendData(char* data)
{
    // Send message
    ResponseStatus response = e32ttl.sendMessage(data);
    // Check the send status
    logger->debug("MESSAGE SENDING STATUS: %s", response.getResponseDescription().c_str());
}
