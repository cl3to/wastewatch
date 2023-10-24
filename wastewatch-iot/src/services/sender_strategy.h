#ifndef SENDER_STRATEGY_H
#define SENDER_STRATEGY_H

#include <string>

class DataSenderStrategy {
public:
    virtual void sendData(const std::string& data) = 0;
    virtual ~DataSenderStrategy() {}
};

#endif
