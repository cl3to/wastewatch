#include "sender.h"

// Context that allows the client switch between strategies to send data
class DataSender {
    private:
        DataSenderStrategy* strategy;

    public:
        DataSender(DataSenderStrategy* strategy) : strategy(strategy) {}

        void setStrategy(DataSenderStrategy* newStrategy) {
            strategy = newStrategy;
        }

        void sendData(const std::string& data) {
            strategy->sendData(data);
        }
};

