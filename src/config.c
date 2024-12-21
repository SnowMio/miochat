#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log.h"

void trim_whitespace(char *str) {
  char *end;

  // trim leading space
  while (isspace((unsigned char)*str)) {
    str++;
  }

  if (*str == 0) {
    return;
  }

  // trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';
}

int parse_config(const char *filename, Config *config) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    log_message(LOG_ERROR, "Cannot open config file.");
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file)) {
    trim_whitespace(line);

    // skip comments '#' and empty lines.
    if (line[0] == '#' || line[0] == '\0') {
      continue;
    }

    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];

    if (sscanf(line, "%[^=]=%s", key, value) == 2) {
      trim_whitespace(key);
      trim_whitespace(value);
    }
  }
}
