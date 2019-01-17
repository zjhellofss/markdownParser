#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "markdown_sentence.h"
#include "../markdown_config.h"
#include "markdown_token.h"
#include "markdown_paragraph.h"

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
    size_t len = 0;
    ssize_t read;
    FILE *input_md = fopen(path, "r");
    FILE *out_md;
    char buf[1024] = {0};
    md_stce st;
    while (true) {
        memset(line, '\0', strlen(line));
        if ((read = getline(&line, &len, input_md)) == -1) {
            break;
        }
        if (!strncmp(line, "```", 3)) {
            size_t l = -1;
            while ((getline(&line, &len, input_md)) != -1 && strcmp(line, "```\n")) {
                l = strlen(line);
                line[l - 1] = '\n';
                sprintf(buf + strlen(buf), "%s", line);
            }
            out_md = fopen(MD_TMP_PATH, "w");
            fwrite(buf, strlen(buf), 1, out_md);
            fflush(out_md);
            init_stce(&st);
            md_token token_tmp;
            init_token(&token_tmp);
            strcpy(token_tmp.str, buf);
            st.types[0] = token_tmp.type = MD_QUOTE_L;
            st.tokens[st.s_size++] = token_tmp;
        } else {
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



