#ifndef HTTPSERV_SERVER_LOG_H
#define HTTPSERV_SERVER_LOG_H

#include <unistd.h>

#define EMERGE "EMERGE"
#define ALERT  "ALERT"
#define WARN  "WARN"
#define INFO "INFO"
#define DEBUG "DEBUG"
typedef int LOG_LEVEL;
#define EMERGE_L  1
#define ALERT_L  2
#define WARN_L  3
#define INFO_L 4
#define DEBUG_L 5
#include "../util/threadpool.h"


void write_log (LOG_LEVEL level, pid_t pid, const char *function,int line,const char *message);

int open_log_fd (threadpool_t *p,const char *log_path);

#endif //HTTPSERV_SERVER_LOG_H
