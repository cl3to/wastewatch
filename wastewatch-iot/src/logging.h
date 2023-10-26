/**

* Logging.h

* This file contains the declaration of the class Logger,
with the methods to log information in a abstract way.
The idea is to abstract the logging mechanism, so that
it can be changed in the future without affecting the
rest of the code.

* For example, we can use the Serial port to log information
or we can implement a x86 version of the logger to be used
in the tests.

*/

#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

class Logger {
    void print(const char * log_prefix, const char *format, va_list args);
    public:
        Logger();
        ~Logger();
        void debug(const char *format, ...);
        void warn(const char *format, ...);
        void error(const char *format, ...);
};
#endif
