#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "markdown_sentence.h"
#include "../markdown_config.h"
#include "markdown_token/markdown_token.h"
#include "markdown_paragraph.h"
#include "../markdown_token/markdown_table.h"

/**
*  语法分析器
*/

void init_stce (md_stce *st) {
    st->s_size = 0;
    memset(st->types, '\0', sizeof(MD_TYPE) * 32);
    memset(st->tokens, '\0', sizeof(md_token) * 32);
}

void process_line (char *path, FILE *f) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fc = fopen(path, "w");
    while ((read = getline(&line, &len, f)) != -1) {
        if (!strcmp(line, "\n")) {
            continue;
        } else {
            fwrite(line, sizeof(char), strlen(line), fc);
        }
    }
    if (line) {
        free(line);
    }
    fclose(fc);
    fclose(f);
}


void process_sentence_ (int read, md_stce *stce) {
    md_token mt;
    FILE *f = fopen(MD_TMP_PATH, "r");
    while (true) {
        init_token(&mt);
        produce_token(&mt, f);
        if (mt.str[mt.m_size - 1] == '\n') {
            mt.str[mt.m_size - 1] = '\0';
        }
        stce->types[stce->s_size] = mt.type;
        stce->tokens[stce->s_size++] = mt;
        if (ftell(f) >= read - 1) {
            break;
        }
    }
    fclose(f);
}

void process_sentence (char *path) {
    char *line = malloc(sizeof(char) * 512);
    char *m_line = line;
    size_t len = 0;
    ssize_t read;
    FILE *input_md = fopen(path, "r");
    FILE *out_md;
    md_stce st;
    int r1, r2;
    while (true) {
        r1 = r2 = -1;
        memset(line, '\0', strlen(line));
        if ((read = getline(&line, &len, input_md)) == -1) {
            break;
        }
        char buf[1024] = {0};
        if (!strncmp(line, "```", 3)) {
            size_t l = -1;
            char lan_type[16];
            strcpy(lan_type, line + 3);
            lan_type[strlen(lan_type) - 1] = '\0';
            strcpy(buf + strlen(buf), lan_type);
            strcpy(buf + strlen(buf), "|");//语言类型的分割符号
            while ((getline(&line, &len, input_md)) != -1 && strncmp(line, "```", 3)) {
                l = strlen(line);
                line[l - 1] = '\n';
                sprintf(buf + strlen(buf), "%s", line);
            }
            init_stce(&st);
            md_token token_tmp;
            init_token(&token_tmp);
            strcpy(token_tmp.str, buf);
            st.types[0] = token_tmp.type = MD_QUOTE_L;
            st.tokens[st.s_size++] = token_tmp;

        } else if (!(r1 = strncmp(line, "\\foot", 5)) || !(r2 = strncmp(line, "\\table", 6))) {
            char *tmp_line = line;//保存原来行缓冲的开始位置
            tmp_line += 5;
            const char *pattern;
            if (!r1) {
                pattern = "\\((.+)\\)\\{.+\\}";
            } else if (!r2) {
                pattern = "\\((.+)\\)\\[.+\\]";
            }
            regex_t preg;
            int res;
            char result[BUFSIZ];
            regmatch_t pmatch[10];
            if ((res = regcomp(&preg, pattern, REG_EXTENDED)) != 0) {
                return;
            }
            res = regexec(&preg, tmp_line, 10, pmatch, REG_NOTBOL);
            if (res == REG_NOMATCH) {
                fseek(input_md, -(strlen(tmp_line)), SEEK_CUR);
                goto es;
            }
            len = pmatch[0].rm_eo - pmatch[0].rm_so;
            memcpy(result, tmp_line + pmatch[0].rm_so, len);
            result[len] = 0;
            init_stce(&st);
            md_token token_tmp;
            init_token(&token_tmp);
            strcpy(token_tmp.str, result);
            if (!r1) {
                /*脚注*/
                st.types[0] = token_tmp.type = MD_FOOT;

            } else if (!r2) {
                /*表格*/
                st.types[0] = token_tmp.type = MD_FORM;
            }
            st.tokens[st.s_size++] = token_tmp;
        } else {
            es:
            out_md = fopen(MD_TMP_PATH, "w");
            size_t l = strlen(line);
            if (line[l - 1] == '\n')
                line[l - 1] = '\0';
            fwrite(line, strlen(line), 1, out_md);
            fflush(out_md);
            fclose(out_md);
            //todo
            init_stce(&st);
            process_sentence_(read, &st);
        }
        push_sentence(st);
    }
    if (line) {
        free(line);
    }

}



