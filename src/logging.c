#include <stdarg.h>
#include <stdio.h>

#include "logging.h"

static int vlog(FILE* out, int color, const char* format, va_list arg) {
    char realFormat[255];

    sprintf(
        realFormat, 
        "\033[1;%dm%s\033[0m",
        color,
        format
    );

    return vfprintf(out, realFormat, arg);
}

int logError(const char* format, ...) {
    va_list arg;
    int done;

    va_start(arg, format);
    fflush(stdout);
    done = vlog(stderr, 31, format, arg);
    va_end(arg);

    return done;
}

int logWarning(const char* format, ...) {
    va_list arg;
    int done;

    va_start(arg, format);
    fflush(stdout);
    done = vlog(stderr, 33, format, arg);
    va_end(arg);

    return done;
}

int logMessage(const char* format, ...) {
    va_list arg;
    int done;

    va_start(arg, format);
    done = vfprintf(stdout, format, arg);
    va_end(arg);

    return done;
}
