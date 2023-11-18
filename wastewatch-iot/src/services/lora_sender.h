#ifndef LORA_SENDER_H
#define LORA_SENDER_H

#include "sender_strategy.h"
#include "../logging.h"

class LoraDataSender : public DataSenderStrategy
{
Logger *logger;
public:
    LoraDataSender(Logger *logger);
    void sendData(char *data) override;
};

#endif
