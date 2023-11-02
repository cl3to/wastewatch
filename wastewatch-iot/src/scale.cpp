#define __MODULE_NAME__ "SCALE"

#include <stdio.h>
#include "scale.h"
#include <cmath>        // Manter a ordem dos imports por conta de um bug
#include <time.h>

Scale::Scale()
{
    logger->debug("initializing scale internal structure");
    for (int i = 0; i < MEASUREMENT_BUFFER_SIZE; i++)
    {
        this->measurements[i] = new Measurement(logger);
        if (!this->measurements[i])
        {
            logger->debug("invalid measurement created");
        }
    }
    this->index = 0; // no data

    _lastUpdate = 0;
    _lastReadFromDevice = 0;
}

// default pins D7 = RX, D8 = TX
Scale::Scale(int _rx, int _tx) : Scale()
{

    this->serial_conn = new SoftwareSerial(_rx, _tx);
    this->index = 0;
    this->rx = _rx;
    this->tx = _tx;
}

Scale::~Scale()
{
    for (int i = 0; i < MEASUREMENT_BUFFER_SIZE; i++)
    {
        if (this->measurements[i])
        {
            delete this->measurements[i];
        }
        this->measurements[i] = NULL;
    }

    // remove serial object
    if (this->serial_conn)
    {
        delete this->serial_conn;
        this->serial_conn = NULL;
    }
}

int Scale::getSampleBefore(Measurement *m, unsigned long seconds)
{

    logger->debug("BEGIN: getSamplesBefore");

    int ix = this->index;
    int cnt = 0;
    while ((cnt < this->samples) && ((m->ts - this->measurements[ix]->ts) < seconds * 1000L))
    {


        logger->debug("getSamplesBefore: %ld | %d | %d < %d", seconds, ix, cnt, this->samples);
        cnt++;
        if (cnt < this->samples)
        {
            ix--;
            if (ix < 0)
            {
                ix = MEASUREMENT_BUFFER_SIZE - 1;
            }
        }
        // yield();

        logger->debug("getSamplesBefore: ix=%d | m=%s | m[ix]=%s | m->ts=%lu | m[ix]->ts=%lu ",
            ix, (m ? "TRUE" : "FALSE"), (this->measurements[ix] ? "TRUE" : "FALSE"),
            (m ? m->ts : 0l),
            (this->measurements[ix] ? this->measurements[ix]->ts : 0l));
    }

    logger->debug("END: getSamplesBefore ( %d )", ix);
    // got the oldest sample to compare to
    return ix;
}

int Scale::getNext(int ix)
{
    ix++;
    if (ix >= MEASUREMENT_BUFFER_SIZE)
        ix = 0;
    return ix;
}

/**
 * calculate some measures over the previously read data
 */
void Scale::calculateMeasures(Measurement *m)
{
    // calculate if this measurement indicates a new plate
    // this happens when the previlously 5s are stable and the weight is greater then previous

    int ix = this->getSampleBefore(m, NUMBER_SECONDS_PER_PLATE);
    int ix1 = ix;
    int ix2 = this->getNext(ix);
    float mean = 0.0;
    int counter = 0;

    logger->debug("BEGIN:calculateMeasures");
    logger->debug("ix1 = %d - %d | ix = %d | samples = %d | index = %.d", ix1, ix2, ix, this->samples, this->index);

    // theres at least 2 samples / measures
    if (this->samples > 2)
    {
        do
        {
            // variation = variation + this->measurements[ix2]->weight_net - this->measurements[ix1]->weight_net;
            mean = mean + this->measurements[ix2]->weight();
            ix1 = ix2;
            ix2 = this->getNext(ix2);
            counter++;
            // yield();
        } while (this->measurements[ix2] != m);

        mean = mean / counter;

        // check if variation of previously samples is small
        // and current varion is greater
        // and the new weight is greater than previous
        //
        // then flat as a new plate

        // condition to update (current weight is less than median weight)
        if (m->weight() < (mean * .9) && m->weight() > (mean * 1.1))
        {
            logger->debug("Valid weight!");
            m->update = 1;
        }

    }
    logger->debug("END:calculateMeasures");
}

/**
 * push a new measurement to the cache, cycling when needed
 */
int Scale::add(Measurement *m)
{

    int retvalue = 0;

    if (!m || (m && m->weight_raw == -1 && m->weight_net == -1 && m->tare == -1))
    {
        // invalid entry
        logger->debug("invalid entry ... discarding");
        if (m)
        {
            m->dump();
        }
    }
    else
    {
        this->samples++;

        this->calculateMeasures(m);

        if (this->shouldUpload(m))
        {
            char payload[300];
            m->payload(payload, 300);

            logger->debug("payload to send = %s", payload);
            if (this->_device)
            {
                // TODO: send data (USING LORA)
                logger->debug("Send data");
            }
            else
            {
                logger->debug("missing device !!!");
            }
        }

        logger->debug("returning from calculate measures");

        if (m)
        {
            logger->debug("T:%.2f N:%.2f TARE:%.2f -- CALC WEIGHT:%.2f", m->weight_raw, m->weight_net, m->tare, m->weight());
        }
        else
        {
            logger->debug("m is NULL");
        }

        this->index = this->getNext(this->index);
    }

    return retvalue;
}

/**
 * flag an auto-restart of the scale when it stays idle for more than three hours
 */
// TODO: Check if this is necessary
bool Scale::shouldReboot()
{
    if (_restartCounter > 180)
    {
        logger->debug("REBOOT!");
        return true;
    }

    return false;
}

// TODO: Check if this is necessary
bool Scale::shouldUpload(Measurement *m)
{
    // reasons to upload this measurement to the platform
    // 1 - relevant event measured on the device
    // 2 - heartbeat (to enable validation of the connection of the device)
    if (((millis() - _lastUpdate) > HEARTBEAT_TIMEOUT_MS))
    {
        _restartCounter++;
    }
    bool ret = (this->samples == 1) || m->isFlagged() || ((millis() - _lastUpdate) > HEARTBEAT_TIMEOUT_MS);

    return ret;
}

void Scale::setDevice(DataSender *device)
{
    _device = device;
    logger->debug("Set device!");
}

void Scale::setLogger(Logger *logger)
{
    this->logger = logger;
}

Measurement *Scale::getCurrent()
{
    if (this->index >= 0)
    {
        return this->measurements[this->index];
    }
    return NULL;
}

/**
 * to hold this sample, adding it to the scale buffer
 */
int Scale::process(char *buffer)
{
    Measurement *m = this->measurements[this->index];
    if (m)
    {
        logger->debug("parsing ...");
        m->parse(buffer, m, logger);
        return this->add(m);
    }
    else
    {
        logger->debug("invalid read from the device = %s", buffer);
    }

    return 0;
}

/**
 * shows the content of read buffer in ASC and HEX
 */
void Scale::dump(char *buffer, int size)
{
    // TODO: Check if this buffer can be smaller
    char pretty[100];

    // dump ascii
    logger->debug("ascii: %s", buffer);

    // calculate space to col 80
    int i;
    for ( i = size; i <= 45; i++)
    {
       pretty[i] = ' ';
    }
    pretty[i++] = ' ';
    pretty[i++] = '|';
    pretty[i++] = ' ';
    pretty[i++] = '\0';

    // dump hex code
    char *hexbuff_ptr = pretty;
    for (i = 0; i < size; i++)
    {
        unsigned char b = buffer[i];
        if (b < 0x10)
            hexbuff_ptr += sprintf(hexbuff_ptr, "%s", " 0");
        else
            hexbuff_ptr += sprintf(hexbuff_ptr, "%s", " ");

        hexbuff_ptr += sprintf(hexbuff_ptr, "0x%02X", b);
    }

    logger->debug("hex: %s", pretty);
}

/**
 * read the scale measurements
 */
int Scale::read()
{
    if (USE_MOCK) {
        return this->readRandomValues();
    }
    else {
        return this->readFromSerial();
    }
}

/**
 * read serial line and fill the read buffer to be processed
 * looking for dataframe finish.
 * possible the first dataframe is junked and should be ignored
 * since the scale is in continous transmission mode
 */
int Scale::readFromSerial() {
    unsigned long ts = millis();
    int ret = 0;
    if (this->state && this->serial_conn->available() > 0)
    {
        // read serial input while there's any data
        char b;

        _buffer[0] = '\0';
        int i = 0;
        bool packet = false;
        while (i < 39 && !packet)
        {
            for (; (b = this->serial_conn->read()) != 0xFF && i < (DATA_BUFFER_SIZE - 1) && !packet;)
            {
                if (b != 0x00 && b != 0x0D)
                {
                    _buffer[i] = b;
                    i++;
                }
                packet = (b == 0x0A);
            }
        }
        if ((i - 1) >= 0 && _buffer[(i - 1)] == 0x0A)
        {
            _buffer[(i - 1)] = '\0';
            i--;
        }
        if ((i - 1) >= 0 && _buffer[(i - 1)] == 0x0D)
        {
            _buffer[(i - 1)] = '\0';
            i--;
        }
        _buffer[i] = '\0';


        this->dump(_buffer, i);
        ret = this->process(_buffer);

        logger->debug("[ %d ]", i);
        _lastReadFromDevice = ts;
    }
    else
    {
        if (!this->state)
        {
            logger->debug("need to initialize the serial first");
        }
    }

    return ret;
}

/**
 * read random generated values for mock purposes
 */
int Scale::readRandomValues() {
    float pb, pl, t;
    unsigned long ts = millis();

    // generate a random seed
    srand(time(NULL));

    pb = (float)rand() / RAND_MAX * 55;
    pl = (float)rand() / RAND_MAX * 50;
    t = (float)rand() / RAND_MAX * 5;

    snprintf(_buffer, sizeof(_buffer), PROTOCOL_FORMAT, pb, pl, t);
    
    _lastReadFromDevice = ts;
    return this->process(_buffer);
}

void Scale::begin()
{
    // this->serial_conn->begin(9600);
    //  software serial version 5.1.0 and up will use this
    this->serial_conn->begin(9600, SWSERIAL_8N1, rx, tx, true, 256, 10);
    this->state = 1;
}

int Scale::getState()
{
    return this->state;
}
