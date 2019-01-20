
#ifndef HTTPSERV_MARKDOWN_SENTENCE_H
#define HTTPSERV_MARKDOWN_SENTENCE_H

#include <stdio.h>
#include "../markdown_config.h"
#include "markdown_token/markdown_token.h"

typedef struct md_stce {
    MD_TYPE types[32];//一个句子中的所有词法
    int s_size;
    md_token tokens[32];
} md_stce;

void process_line (char *path, FILE *f);

void process_sentence (char *path);

#endif //HTTPSERV_MARKDOWN_SENTENCE_H
