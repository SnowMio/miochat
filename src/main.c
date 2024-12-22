#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "version.h"

#define CONFIG_FILE "config.cfg"

// default settings
#define DEFAULT_PORT 8080
#define DEFAULT_WELCOME_MESSAGE "Welcome to MioChat!"
#define DEFAULT_DB_PATH "data.db"
#define DEFAULT_IS_DEBUG 1

typedef struct {
  int port;
  char welcome_message[256];
  char db_path[256];
  int is_debug;
} Config;

extern int read_config(const char *filename, Config *config);
extern int create_default_config(const char *filename, const Config *config);

int main(int argc, char *argv[]) {

  log_message(LOG_INFO, "Welcome to MioChat v%s", VERSION);

  Config config;

  // try to read config file
  if (read_config(CONFIG_FILE, &config) != 0) {
    log_message(LOG_WARN,
                "Failed to read config file. Trying to create a new one.");

    Config default_config = {DEFAULT_PORT, DEFAULT_WELCOME_MESSAGE,
                             DEFAULT_DB_PATH, DEFAULT_IS_DEBUG};
    if (create_default_config(CONFIG_FILE, &default_config) != 0) {
      log_message(LOG_ERROR, "Failed to create config file.");
      return 1;
    }

    config = default_config;
  }

  log_message(LOG_INFO, "Server is running on port %d", config.port);
  log_message(LOG_INFO, "Data is %s", config.db_path);

  if (config.is_debug == 1) {
    log_message(LOG_WARN, "Server is running on DEBUG mode.");
  }

  return 0;
}

int read_config(const char *filename, Config *config) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return -1; // file not found
  }

  // read config items
  if (fscanf(file, "port=%d\n", &config->port) != 1 ||
      fscanf(file, "welcome_message=%255[^\n]\n", config->welcome_message) !=
          1 ||
      fscanf(file, "db_path=%255[^\n]\n", config->db_path) != 1 ||
      fscanf(file, "is_debug=%d\n", &config->is_debug) != 1) {
    fclose(file);
    return -1; // config file format wrong
  }

  fclose(file);
  return 0; // success read config file
}

int create_default_config(const char *filename, const Config *config) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return -1; // file create failed
  }

  fprintf(file, "port=%d\n", config->port);
  fprintf(file, "welcome_message=%s\n", config->welcome_message);
  fprintf(file, "db_path=%s\n", config->db_path);
  fprintf(file, "is_debug=%d\n", config->is_debug);

  fclose(file);
  return 0; // success create file
}
