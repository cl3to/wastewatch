/**
 * SCALE
 * ------------------------------------------------------------------------------------------
 * implements a program to communicate with scale (michaletti A-100)
 * and send the current weight information to KONKER platform
 *
 * version | developer | comment
 * ------------------------------------------------------------------------------------------
 * 1.0       alexjunq    first implementation and usage of KONKER virtual device abstraction
 * ------------------------------------------------------------------------------------------
 * copyright(c) by Konker 2018
 */

// uncomment the following line to generated debug information on Serial line
// to be monitored using a serial terminal

// #define DEBUG

#include <Arduino.h>
#include "scale.h"
#include "logging.h"
#include "services/sender.h"
#include "services/test_sender.h"

#define __APP_VERSION__ "0.0.1"

// create a scale device (physical) and inform digital PINS used to create a software serial
// communication
// Scale scale(D6,D7); // scale 1
Scale scale(A4, A5); // scale 2

Logger *logger;
TestDataSender *testStrategy;
DataSender *sender;

/**
 * initialize the program, creating a new logical device, and linking it to the physical device
 */
void setup()
{
    logger = new Logger();
    logger->debug("initializing");

    testStrategy = new TestDataSender(logger);
    sender = new DataSender(testStrategy);

    scale.setDevice(sender);
    scale.setLogger(logger);
    // TODO: Add app status
    // TODO: Start application
    // TODO: LoraWAN setup
}

/**
 * main loop of the app
 * just check connection, and if available, make a reading on the physical connected device
 * this read triggers internally the logic to verify if the reading need to be replicated
 * to the logical device ... if so, maintain it synchronized automatically
 *
 */
void loop()
{
    logger->debug("looping");
    delay(1000);
    if (scale.getState())
    {
        scale.read();
    }
    else
    {
        logger->debug("setting up scale...");
        scale.begin();
        logger->debug("scale started");
    }

    if (scale.shouldReboot())
    {
        logger->debug(">>>>>>>>>>> restarting after too much time idle ... ");
    }
}
