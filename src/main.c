#include "log.h"
#include "version.h"

int main(int argc, char *argv[]) {
  log_message(LOG_INFO, "Welcome to MioChat v%s", VERSION);

  log_message(LOG_WARN, "This is a test Warning message.");
  log_message(LOG_ERROR, "This is a test Error message.");

  return 0;
}
