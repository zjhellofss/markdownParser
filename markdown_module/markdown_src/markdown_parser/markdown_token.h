
#ifndef HTTPSERV_MARKDOWN_TOKEN_H
#define HTTPSERV_MARKDOWN_TOKEN_H

#include "../markdown_config.h"
#include <stdio.h>
typedef struct md_token {
    MD_TYPE type;
    int m_size;
    char str[1024];//用来储存对应MD类型的的字符串
} md_token;
#define MAX_TOKEN_SIZE 1024



void init_token (md_token *token);

void produce_token (md_token *mt, FILE *f);

void read_token (md_token *mt, FILE *f);

void skip_space (char *file_path);

#endif //HTTPSERV_MARKDOWN_TOKEN_H

