#include "log.h"
#include <stdarg.h>
#include <time.h>

LogLevel CURRENT_LOG_LEVEL = LOG_INFO;

void log_message(LogLevel level, const char *file, int line, const char *fmt, ...) {
    if (level < CURRENT_LOG_LEVEL) return;

    const char *level_str;
    const char *color;

    switch (level) {
        case LOG_INFO:  level_str = "INFO";  color = LOG_COLOR_INFO;  break;
        case LOG_WARN:  level_str = "WARN";  color = LOG_COLOR_WARN;  break;
        case LOG_ERROR: level_str = "ERROR"; color = LOG_COLOR_ERROR; break;
        case LOG_DEBUG: level_str = "DEBUG"; color = LOG_COLOR_DEBUG; break;
        default:        level_str = "LOG";   color = LOG_COLOR_RESET; break;
    }


    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", t);
    
    fprintf(stderr, "%s[%s] %s (%s:%d): ", color, level_str, time_buf, file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "%s\n", LOG_COLOR_RESET);
}
