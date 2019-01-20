

#ifndef HTTPSERV_MARKDOWN_PARAGRAPH_H
#define HTTPSERV_MARKDOWN_PARAGRAPH_H


#include "../markdown_config.h"
#include "markdown_sentence.h"
#include <string.h>
#include <stdlib.h>

typedef struct markdown_paragraph {
    int line_sum;
    md_stce stces[MD_MAX_STCE];
} markdown_prg;

//todo 与容量有关的数据结构都应该改为动态构造的
void init_paragraph ();

void push_sentence (md_stce stce);

char *produce_underline (char *str);

void pop_sentence (char *file_path);

char *produce_img_link (char *img_link);

char *produce_checkbox (char c);

char *produce_link_link (char *link);

char *produce_highlight (char *str);

#endif //HTTPSERV_MARKDOWN_PARAGRAPH_H
