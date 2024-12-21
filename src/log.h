#ifndef __MIOCHAT_LOG
#define __MIOCHAT_LOG

#include <stdio.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "latest.log"

typedef enum {
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
} LogLevel;

void log_message(LogLevel level, const char *message, ...);

#endif // __MIOCHAT_LOG
