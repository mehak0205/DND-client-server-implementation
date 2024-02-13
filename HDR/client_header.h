#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

// Log levels
#define LOG_LEVEL_FATAL    0
#define LOG_LEVEL_INFO     1
#define LOG_LEVEL_WARNING  2
#define LOG_LEVEL_DEBUG    3

// Macro for logging messages
#define LOG(level, msg) \
    do { \
        if (level <= LOG_LEVEL_DEBUG) { \
            printf("[%s] %s\n", log_levels[level], msg); \
        } \
    } while (0)
