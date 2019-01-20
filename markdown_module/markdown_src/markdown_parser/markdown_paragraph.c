
#include <string.h>
#include "markdown_paragraph.h"
#include "markdown_sentence.h"
#include "../markdown_convert/markdown_tohtml.h"
#include <stdlib.h>
#include <zconf.h>


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

/*<input type="checkbox" checked>*/
char *produce_checkbox (char c) {
    char *buf = malloc(sizeof(char) * 48);
    memset(buf, '\0', 48);
    strcpy(buf, "<input type=\"checkbox\" ");
    if (c == 'x') {
        strcpy(buf + strlen(buf), "checked");
    } else if (c == 'y') { ;
    }
    strcpy(buf + strlen(buf), ">");
    return buf;
}

char *produce_link_link (char *link) {
    char *link_name = malloc(sizeof(char) * 48);
    char *o_l = link_name;
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

    char *buf = malloc(sizeof(char) * 128);
    memset(buf, '\0', 128);

    strcpy(buf + strlen(buf), "<a href=\"");
    strcpy(buf + strlen(buf), link_ref);
    strcpy(buf + strlen(buf), "\">");
    strcpy(buf + strlen(buf), link_name);
    strcpy(buf + strlen(buf), "</a>");
    free(o_l);
    free(o_l2);
    return buf;
}

/*<font style="color:red">A paragraph</font>*/
char *produce_highlight (char *str) {
    char *buf = malloc(sizeof(char) * 96);
    memset(buf, '\0', 96);
    strcpy(buf + strlen(buf), "<font style=\"color:red\">");
    strcpy(buf + strlen(buf), str);
    strcpy(buf + strlen(buf), "</font>");
    return buf;
}

char *produce_underline (char *str) {
    char *buf = malloc(sizeof(char) * 96);
    memset(buf, '\0', 96);
    strcpy(buf + strlen(buf), "<u>");
    strcpy(buf + strlen(buf), str);
    strcpy(buf + strlen(buf), "</u>");
    return buf;
}

/**
 *
 *  <ul class="list-group">
 *  <a href="#" class="list-group-item active"><h4 class="list-group-item-heading"></h4></a>
 *	<li class="list-group-item"></li>
 *	<li class="list-group-item"></li>
 *	</ul>
 */
char *produce_foot (char *str) {
    char *buf = malloc(1024 * sizeof(char));
    memset(buf, '\0', strlen(buf));
    char *tstr = malloc(96 * sizeof(char));
    memset(tstr, '\0', strlen(tstr));
    strcpy(buf, "<ul class=\"list-group\">");
    strcpy(buf + strlen(buf), "<a href=\"#\" class=\"list-group-item active\"><h4 class=\"list-group-item-heading\">");
    int i = 0;
    int j = 0;
    char c;
    while (true) {
        c = str[i];
        if (c == '(') {
            i++;
            continue;
        } else if (c == ')') {
            i++;
            break;
        } else {
            /*读到的标题*/
            tstr[j++] = c;
            i++;
        }
    }
    strcpy(buf + strlen(buf), tstr);
    strcpy(buf + strlen(buf), "</h4></a>");
    memset(tstr, '\0', strlen(tstr));
    int n = 0;
    for (int k = i; k < strlen(str); ++k) {
        if (str[k] == '{') {
            n++;
        }
    }


    for (int u = 0; u < n; ++u) {
        memset(tstr, '\0', strlen(tstr));
        j = 0;
        while (true) {
            c = str[i];
            if (c == '{') {
                i++;
                continue;
            } else {
                if (c == '}') {
                    strcpy(buf + strlen(buf), "<li class=\"list-group-item\">");
                    strcpy(buf + strlen(buf), tstr);
                    strcpy(buf + strlen(buf), "</li>");
                    i++;
                    break;
                } else {
                    tstr[j++] = c;
                }
                i++;
            }
        }
    }
    return buf;
}

char *produce_table (char *tstr) {
    char *buf = malloc(1024 * sizeof(char));
    strcpy(buf, "<table class=\"table table-striped table-bordered\"  ><tr>");
    char *tmp_str = malloc(96 * sizeof(char));
    //读表格的标题
    int i = 0;
    int j = 0;
    char c;
    while (true) {
        c = tstr[i];
        if (c == '(') {
            i++;
            continue;
        } else {
            if (c == ',') {
                strcpy(buf + strlen(buf), "<th>");
                strcpy(buf + strlen(buf), tmp_str);
                strcpy(buf + strlen(buf), "</th>");
                memset(tmp_str, '\0', strlen(tmp_str));
                j = 0;

            } else if (c == ')') {
                strcpy(buf + strlen(buf), "<th>");
                strcpy(buf + strlen(buf), tmp_str);
                strcpy(buf + strlen(buf), "</th>");
                strcpy(buf + strlen(buf), "</tr>");
                memset(tmp_str, '\0', strlen(tmp_str));
                i++;
                break;
            } else {
                tmp_str[j++] = c;
            }
            i++;
        }
    }
    int n = 0;
    for (int k = i; k < strlen(tstr); ++k) {
        if (tstr[k] == '[') {
            n++;
        }
    }
    for (int u = 0; u < n; ++u) {
        strcpy(buf + strlen(buf), "<tr>");
        j = 0;
        while (true) {
            char c = tstr[i];
            if (c == '[') {
                i++;
                continue;
            } else {
                if (c == ',') {
                    strcpy(buf + strlen(buf), "<td>");
                    strcpy(buf + strlen(buf), tmp_str);
                    strcpy(buf + strlen(buf), "</td>");
                    memset(tmp_str, '\0', strlen(tmp_str));
                    j = 0;

                } else if (c == ']') {
                    strcpy(buf + strlen(buf), "<td>");
                    strcpy(buf + strlen(buf), tmp_str);
                    strcpy(buf + strlen(buf), "</td>");
                    strcpy(buf + strlen(buf), "</tr>");
                    i++;
                    break;
                } else {
                    tmp_str[j++] = c;
                }
                i++;
            }
        }
    }
    strcpy(buf + strlen(buf), "</table>");
    free(tmp_str);
    return buf;
}

/*
 * <pre><code class="html"> </code></pre>
 * */
char *produce_quoteblock (char *str) {
    char *buf = malloc(4096 * sizeof(char));
    memset(buf, '\0', strlen(buf));
    int i = 0;
    while (str[i] != '|') {
        i++;
    }
    char type[16];
    strncpy(type, str, i);
    strcpy(buf + strlen(buf), "<pre><code class=\"");
    strcpy(buf + strlen(buf), type);
    strcpy(buf + strlen(buf), "\">");
    strcpy(buf + strlen(buf), str + i + 1);
    strcpy(buf + strlen(buf), "</code></pre>");
    return buf;
}

void pop_sentence (char *file_path) {
    char *md_html_start[36] = {"<ul><li>", "<ol><li>", "<del>", "<h1>", "<h2>",
                               "<h3>", "<h4>", "<h5>", "<h6>",
                               "<h7>", "<i>", "<b>", "<code>", "<pre><xmp>", "<p>", "<a>", "<img>", "<blockquote>",
                               "<hr/>", ""};


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
    produce_tmp_html_file(file_path, NULL, true);
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
        bool is_done;
        char buf[4096] = {0};
        stce = prg->stces[i];
        if (stce.s_size != -1) {
            memset(buf, '\0', strlen(buf));
            strcpy(buf + strlen(buf), "<p>");
            for (j = 0; j < stce.s_size; ++j) {
                is_done = false;
                token = stce.tokens[j];
                do {
                    char *tmp_buf;
                    if (token.type == MD_HIGHLIGHT) {
                        tmp_buf = produce_highlight(token.str);
                        is_done = true;/*不加这条程序会宕*/

                    } else if (token.type == MD_CHECKBOX) {
                        tmp_buf = produce_checkbox(token.str[0]);
                        is_done = true;
                    } else if (token.type == MD_UNDER) {
                        tmp_buf = produce_underline(token.str);
                        is_done = true;
                    } else if (token.type == MD_FORM) {
                        tmp_buf = produce_table(token.str);
                        is_done = true;
                    } else if (token.type == MD_FOOT) {
                        tmp_buf = produce_foot(token.str);//生成脚注
                        is_done = true;
                    } else if (token.type == MD_QUOTE_L) {
                        tmp_buf = produce_quoteblock(token.str);//生成脚注
                        is_done = true;
                    }
                    if (is_done) {
                        strcpy(buf + strlen(buf), tmp_buf);
                        free(tmp_buf);
                        stce.tokens[j].type = -1;
                    }
                } while (0);
                if (token.type == MD_IMG || token.type == MD_LINK) {
                    char *tmp_buf;
                    if (token.type == MD_IMG) {
                        tmp_buf = produce_img_link(token.str);
                        strcpy(buf + strlen(buf), tmp_buf);
                        free(tmp_buf);
                    } else {
                        tmp_buf = produce_link_link(token.str);
                        strcpy(buf + strlen(buf), tmp_buf);
                        free(tmp_buf);
                    }
                } else {
                    if (!is_done) {
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
            strcpy(buf + strlen(buf), "</p>");
        }
        produce_tmp_html_file(file_path, buf, false);
    }
    char end_buf[24];
    strcpy(end_buf + strlen(end_buf), "</body></html>");
    produce_tmp_html_file(file_path, end_buf, false);
    free(prg);

}

