#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

extern LogLevel CURRENT_LOG_LEVEL;

#define LOG_COLOR_RESET   "\x1b[0m"
#define LOG_COLOR_INFO    "\x1b[32m"
#define LOG_COLOR_WARN    "\x1b[33m"
#define LOG_COLOR_ERROR   "\x1b[31m"
#define LOG_COLOR_DEBUG    "\x1b[36m"

#define log_debug(fmt, ...) \
    if (CURRENT_LOG_LEVEL <= LOG_DEBUG) log_message(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)  \
    if (CURRENT_LOG_LEVEL <= LOG_INFO) log_message(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)  \
    if (CURRENT_LOG_LEVEL <= LOG_WARN) log_message(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) \
    if (CURRENT_LOG_LEVEL <= LOG_ERROR) log_message(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)



void log_message(LogLevel level, const char *file, int line, const char *fmt, ...);

#endif
