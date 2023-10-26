#include <cstdio>
#include <stdio.h>
#include <string>
#include <Arduino.h>
#include "logging.h"


#define SERIAL_BOUD_RATE 115200
#define DEBUG

Logger::Logger() {
    Serial.begin(SERIAL_BOUD_RATE);

}

Logger::~Logger() {
    Serial.end();
}

void Logger::print(const char *log_prefix, const char *format, va_list args) {
    char buffer[256];
    vsprintf(buffer, format, args);
#ifdef DEBUG
    Serial.print(log_prefix);
    Serial.println(buffer);
#endif
    va_end(args);
}

void Logger::debug(const char *format, ...) {
    // Call print with the prefix DEBUG
    va_list args;
    va_start(args, format);
    print("DEBUG: ", format, args);
}

void Logger::warn(const char *format, ...) {
    // Call print with the prefix WARN
    va_list args;
    va_start(args, format);
    print("WARN: ", format, args);
}

void Logger::error(const char *format, ...) {
    // Call print with the prefix ERROR
    va_list args;
    va_start(args, format);
    print("ERROR: ", format, args);
}
