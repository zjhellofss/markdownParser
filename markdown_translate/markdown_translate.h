

#ifndef PARSER_TRANSLATE_H
#define PARSER_TRANSLATE_H

#include <stdio.h>

#define SNODE 0
#define DNODE 1
#define STYPE int
struct ttstr_src_node {
    char *str;
};
struct ttstr_dst_node {
    char *str;
};

struct res_node_list {
    struct ttstr_src_node ts_src_lists[512];
    struct ttstr_dst_node ts_dst_lists[512];
    int d_len;
    int s_len;
};

struct memory_struct {
    char *memory;
    size_t size;
};

struct res_node_list *markdown_passage_translate (char *qstr);

#endif //PARSER_TRANSLATE_H
