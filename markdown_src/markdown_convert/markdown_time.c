#include "markdown_time.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char *get_current_time () {
    time_t t;
    struct tm *lt;
    char *buf = malloc(128);
    memset(buf, '\0', 128);
    time(&t);
    lt = localtime(&t);
    sprintf (buf, "%d/%d/%d %02d:%02d:%02d\n", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min,
             lt->tm_sec);
    return buf;
}