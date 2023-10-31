#ifndef TEST_SENDER_H
#define TEST_SENDER_H

#include <iostream>

#include "sender_strategy.h"
#include "../logging.h"

class TestDataSender : public DataSenderStrategy
{
Logger *logger;
public:
    TestDataSender(Logger *logger);
    void sendData(char *data) override;
};

#endif