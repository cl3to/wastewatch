#include "sender.h"
#include "lorawan_sender.h"

int main() {
    LoRaWANDataSender lorawanStrategy;

    DataSender sender(&lorawanStrategy);

    sender.sendData("Data via LoRaWAN");

    return 0;
}