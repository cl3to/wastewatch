#include "test_sender.h"


TestDataSender::TestDataSender(Logger *logger) {
    this->logger = logger;
}

void TestDataSender::sendData(const std::string &data)
{
    // Simulates the sending of messages
    logger->debug("Sending Data: %s", data);
}
