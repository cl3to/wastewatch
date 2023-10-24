#ifndef LORAWAN_SENDER_H
#define LORAWAN_SENDER_H

#include <iostream>

#include "Arduino.h"
#include "../../libraries/LoRa_E32/LoRa_E32.h"

#include "sender_strategy.h"

class LoRaWANDataSender : public DataSenderStrategy
{
public:
    LoRaWANDataSender();
    void sendData(const std::string &data) override;

private:
    // ---------- esp32 pins --------------
    // TODO: Add constants for the asp pins
    LoRa_E32 e32ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1
};

#endif