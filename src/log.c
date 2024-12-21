#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log.h"

void log_message(LogLevel level, const char *message, ...) {
  FILE *log_file = fopen(LOG_FILE, "a");
  if (log_file == NULL) {
    perror("Error on opening log file");
    return;
  }

  time_t raw_time;
  struct tm *time_info;
  char time_buffer[9]; // format [HH:MM:SS]

  time(&raw_time);
  time_info = localtime(&raw_time);
  strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", time_info);

  const char *level_str;
  switch (level) {
  case LOG_INFO:
    level_str = "INF";
    break;
  case LOG_WARN:
    level_str = "WAR";
    break;
  case LOG_ERROR:
    level_str = "ERR";
    break;
  default:
    level_str = "UNK"; // UNKNOWN
  }

  va_list args;
  va_start(args, message);

  fprintf(log_file, "[%s] %s ", time_buffer, level_str);
  vfprintf(log_file, message, args);
  fprintf(log_file, "\n");

  printf("[%s] %s ", time_buffer, level_str);
  vprintf(message, args);
  printf("\n");

  va_end(args);

  fclose(log_file);
}
