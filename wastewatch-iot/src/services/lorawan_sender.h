#ifndef LORAWAN_SENDER_H
#define LORAWAN_SENDER_H

#include "sender_strategy.h"

class LoRaWANDataSender : public DataSenderStrategy {
public:
    void sendData(const std::string& data) override;
};

#endif