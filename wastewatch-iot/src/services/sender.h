#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <string>

#include "sender_strategy.h"

class DataSender {
private:
    DataSenderStrategy* dataSendingStrategy;

public:
    DataSender(DataSenderStrategy* strategy) : dataSendingStrategy(strategy) {}

    void sendData(char *data) {
        dataSendingStrategy->sendData(data);
    }

    void setStrategy(DataSenderStrategy* strategy) {
        dataSendingStrategy = strategy;
    }
};

#endif
