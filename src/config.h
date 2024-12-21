#ifndef __MIOCHAT_CONFIG
#define __MIOCHAT_CONFIG

typedef struct {
  int server_port;
  char welcome_message[1024];
  char db_file[256];
} Config;

#define MAX_LINE_LENGTH 256

extern void trim_whitespace(char *str);

extern int parse_config(const char *filename, Config *config);

#endif // __MIOCHAT_CONFIG
