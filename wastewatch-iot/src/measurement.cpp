#define __MODULE_NAME__ "MEASUREMENTS"

#include <stdio.h>
#include <string.h>
#include "measurement.h"

void Measurement::copy(Measurement *m) {
    if (m) {
        this->ts = m->ts;
        this->weight_raw = m->weight_raw;
        this->weight_net = m->weight_net;
        this->tare = m->tare;
        this->update = m->update;
    } else {
        logger->debug("invalid M");
    }
}

Measurement::Measurement(Measurement *m) {
    this->copy(m);
}

Measurement::Measurement(Logger *logger) {
    this->logger = logger;
    this->reset();
}

void Measurement::reset() {
    this->ts = millis();
    this->weight_raw = -1.0; // -1 is a start value used to check if the value on the scale is real or reset by program
    this->weight_net = -1.0;
    this->tare = -1.0;
    this->update = 0;  // some other distinct event that should trigger saving on the platform 
}

Measurement::~Measurement() {

}

/**
 * indicate if this sample measurement has some active flag 
 * that indicates that it should be send to the cloud
 */
boolean Measurement::isFlagged() {
    return this->update; 
}

/**
 * parse a dataframe directly read from serial line 
 * into a new object of this structure, returning a
 * new Measurement object when OK or NULL when something 
 * was wrong on processing
 * 
 */
Measurement* Measurement::parse(char *buffer, Measurement *obj, Logger *logger) {
    // parse data on a new measurement 
    Measurement* m = NULL; 

    if (strlen(buffer) < 30) {
        // wrong size of buffer
        logger->debug("size of buffer is %d", strlen(buffer));    
        logger->error("size of buffer %d ... expected 31 or 32", strlen(buffer));
        m = NULL;
    } else {
        logger->debug("reformatting dataframe to parse");
        for (byte i=0; i < strlen(buffer); i++) {
            if (buffer[i] == ',')
                buffer[i] = '.';
            //yield();
        }

        if (obj)  {
            m = obj; // reuse previously created object // to avoid memory fragmentation
            logger->debug("reuse previously created object");
            m->reset();
        } else {
            m = new Measurement(logger);
            logger->debug("create new object");
        }

        // just an adjustement to read partial information from the device when just one character is missing
        // the point here is that when a weight is placed over the scale, it takes some time to adjust 
        // the final read (stabilize) and sometimes when this happens, one byte is "lost" in communication,
        // since the previously data is been send to the platform (there's just one core in the ESP)
        // so no multithreading is possible ...
        // possible solutions are use the more advanced ESP32 (multicore) or other more potent device
        //
        if (strlen(buffer) == 36) 
            sscanf(buffer, PROTOCOL_FORMAT2, &(m->weight_raw), &(m->weight_net), &(m->tare));
        else
            sscanf(buffer, PROTOCOL_FORMAT, &(m->weight_raw), &(m->weight_net), &(m->tare));

        logger->debug("parsed");
    }

    return m;
}

void Measurement::dump() {
    char aux[255];
    snprintf(aux, 255, "W-RAW:%.2f W-NET:%.2f TARE:%.2f UPDATE:%d", 
        this->weight_raw, this->weight_net, this->tare, this->update);
    aux[254] = '\0';
    logger->debug(aux);
}

void Measurement::payload(char* aux, int size, char* restaurant) {
    snprintf(aux, size, "{\"R\": %s, \"P\": %.2f}",
        restaurant, this->weight_net);
    aux[size-1] = '\0';
}

float Measurement::weight() {
    float w = 0.0;
    w = (weight_net ? weight_net : weight_raw);
    if (tare) 
        w = w + tare;
    return w;
}
 