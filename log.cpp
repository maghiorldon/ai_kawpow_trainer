#include "log.h"
#include <cstdarg>
#include <ctime>

void log_with_prefix(const char* prefix, const char* fmt, va_list args) {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("%s %s ", buf, prefix);
    vprintf(fmt, args);
    printf("\n");
}

void log_info(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_with_prefix("[INFO]", fmt, args);
    va_end(args);
}

void log_error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log_with_prefix("[ERROR]", fmt, args);
    va_end(args);
}
