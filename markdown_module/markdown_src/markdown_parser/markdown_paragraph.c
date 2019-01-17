
#include <string.h>
#include "markdown_paragraph.h"
#include "markdown_sentence.h"
#include "../markdown_convert/markdown_tohtml.h"
#include <stdlib.h>


markdown_prg *prg = NULL;

//todo 与容量有关的数据结构都应该改为动态构造的
void init_paragraph () {
    prg = malloc(sizeof(struct markdown_paragraph));
    prg->line_sum = 0;
    memset(prg->stces, '\0', sizeof(prg->stces));
}

void push_sentence (md_stce stce) {
    if (!prg) {
        init_paragraph();
    }
    prg->stces[prg->line_sum] = stce;
    prg->line_sum++;
}
/**
    * "<del>", "<i>", "<b>","<code>", "<p>", "<a>", "<img>" 是需要立刻闭合的标签
*/
bool is_bracket_tag (MD_TYPE type) {
    if (type == -1) {
        return false;
    }
    switch (type) {
        case MD_DEL:
        case MD_ILY:
        case MD_IMPT:
        case MD_QUOTE_S:
        case MD_LINE:
        case MD_LINK:
        case MD_IMG:
            return true;
        default:
            return false;
    }
}

char *produce_img_link (char *img_link) {
    char *buf = malloc(sizeof(char) * 256);
    memset(buf, '\0', 256);
    strcpy(buf + strlen(buf), "<img src=\"");
    strcpy(buf + strlen(buf), img_link);
    strcpy(buf + strlen(buf), "\"/>");
    return buf;
}

char *produce_link_link (char *link) {
    char *link_name = malloc(sizeof(char) * 48); char *o_l = link_name;
    memset(link_name, '\0', 48);
    char *link_ref = malloc(sizeof(char) * 48);
    char *o_l2 = link_ref;
    memset(link_ref, '\0', 48);
    char *ptr = strchr(link, ']');
    strncpy(link_name, link, ptr - link);
    ptr += 2;
    link_name += 1;
    ptr[strlen(ptr) - 1] = '\0';
    link_ref = ptr;

    char *buf  = malloc(sizeof(char)*128);
    memset(buf,'\0',128);

    strcpy(buf + strlen(buf), "<a href=\"");
    strcpy(buf + strlen(buf), link_ref);
    strcpy(buf+strlen(buf),"\">");
    strcpy(buf+strlen(buf),link_name);
    strcpy(buf+strlen(buf),"</a>");
    free(o_l);
    free(o_l2);
    return buf;
}

void pop_sentence (char *file_path) {
    char *md_html_start[36] = {"<ul><li>", "<ol><li>", "<del>", "<h1>", "<h2>",
                               "<h3>", "<h4>", "<h5>", "<h6>",
                               "<h7>", "<i>", "<b>", "<code>", "<pre><xmp>", "<p>", "<a>", "<img>", "<blockquote>",
                               "<hr/>"};


    char *md_html_end[36] = {"</li></ul>", "</li></ol>", "</del>", "</h1>", "</h2>",
                             "</h3>", "</h4>", "</h5>", "</h6>",
                             "</h7>", "</i>", "</b>", "</code>", "</xmp></pre>", "</p>", "</a>", "</img>",
                             "</blockquote>", "",
    };
    int i, j, k;
    md_stce stce;
    md_token token;
    int pi = -1;
    bool is_block = false;
    produce_html_file(file_path,NULL,true);
    for (i = 0; i < prg->line_sum; ++i) {
        if (prg->stces[i].types[0] == MD_BLOCK) {
            if (!is_block) {
                is_block = true;
                stce = prg->stces[i];
                pi = i;
            } else {
                md_stce tmp = prg->stces[i];
                for (j = 1; j < prg->stces[i].s_size; ++j) {
                    token = tmp.tokens[j];
                    memmove(&stce.tokens[stce.s_size++], &token, sizeof(token));
                    prg->stces[pi] = stce;
                }
                prg->stces[i].s_size = -1;

            }
        } else {
            is_block = false;
        }
    }
    for (i = 0; i < prg->line_sum; ++i) {
        char buf[1024] = {0};
        stce = prg->stces[i];
        if (stce.s_size != -1) {
            for (j = 0; j < stce.s_size; ++j) {
                token = stce.tokens[j];
                if (token.type == MD_IMG || token.type == MD_LINK) {
                    char *tmp_buf;
                    if (token.type == MD_IMG) {
                        tmp_buf = produce_img_link(token.str);
                        strcpy(buf+strlen(buf), tmp_buf);
                        free(tmp_buf);
                    } else {
                        tmp_buf = produce_link_link(token.str);
                        strcpy(buf+strlen(buf),tmp_buf);
                        free(tmp_buf);
                    }
                } else {
                    if (token.type == MD_PLAIN && j != 0) {
                        token.type = stce.tokens[j].type = -1;
                    } else {
                        strcpy(buf + strlen(buf), md_html_start[token.type]);
                    }
                    if (strcmp(token.str, "")) {
                        strcpy(buf + strlen(buf), token.str);
                    }
                    if (is_bracket_tag(token.type) ||
                        (j != 0 && (token.type == MD_UD_LIST || token.type == MD_OD_LIST))) {
                        strcpy(buf + strlen(buf), md_html_end[token.type]);
                        stce.tokens[j].type = -1;
                    }
                }
            }
            /*补充结束标签*/
            for (k = stce.s_size - 1; k >= 0; --k) {
                token = stce.tokens[k];
                if (token.type == MD_IMG) {
                    continue;
                }
                if (token.type != -1) {
                    strcpy(buf + strlen(buf), md_html_end[token.type]);
                }
            }
        }
        produce_html_file(file_path,buf,false);
    }
    char end_buf[24];
    strcpy(end_buf + strlen(end_buf), "</body></html>");
    produce_html_file(file_path,end_buf,false);
    free(prg);

}