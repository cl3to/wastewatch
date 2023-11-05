#ifndef LORA_SENDER_H
#define LORA_SENDER_H

#include "LoRa_E32.h"

#include "sender_strategy.h"
#include "../logging.h"

// Applicable for E32-TTL-1W, E32 (433T30S), E32 (868T30S), E32 (915T30S)
#define E32_TTL_100
#define FREQUENCY_915

class LoraDataSender : public DataSenderStrategy
{
Logger *logger;
public:
    LoraDataSender(Logger *logger);
    void sendData(char *data) override;
};

#endif