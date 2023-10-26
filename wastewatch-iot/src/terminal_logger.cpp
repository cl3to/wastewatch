#include <cstdio>
#include <stdio.h>

#include "logging.h"


Logger::Logger() {
    printf("Logger started\n");
}

Logger::~Logger() {
    printf("Logger stopped\n");
}

void Logger::print(const char *log_prefix, const char *format, va_list args) {
    char buffer[256];
    vsprintf(buffer, format, args);
    printf("%s%s\n", log_prefix, buffer);
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
