
#ifndef PARSER_MARKDOWN_HEADNODES_H
#define PARSER_MARKDOWN_HEADNODES_H

#include <string.h>

typedef int HEAD_LEVEL;
#define HEAD1 0x01
#define HEAD2 0x02
#define HEAD3 0x03
#define HEAD4 0x04
#define HEAD5 0x05
#define HEAD6 0x06
#define HEAD7 0x07
#include <markdown_config.h>

#define NODE_LEN 0x80
#define STR_LEN 0x400
struct head_node {
    HEAD_LEVEL level;
    char head_content[STR_LEN];
};
struct head_nodelist {
    struct head_node nodes[NODE_LEN];
    int l;
    bool is_init;
};
typedef struct head_node head_node;
typedef struct head_nodelist nodelist;

void nodelist_insert (struct head_nodelist *list, head_node node);

void init_head_nodeList (struct head_nodelist *list);

#endif //PARSER_MARKDOWN_HEADNODES_H
