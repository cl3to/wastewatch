#ifndef SENDER_STRATEGY_H
#define SENDER_STRATEGY_H

#include <string>

class DataSenderStrategy {
public:
    virtual void sendData(char *data) = 0;
    virtual ~DataSenderStrategy() {}
};

#endif
