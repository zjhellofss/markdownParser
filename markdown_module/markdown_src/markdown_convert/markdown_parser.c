#include <stdlib.h>
#include <markdown_token/markdown_token.h>
#include <markdown_sentence.h>
#include <markdown_paragraph.h>

void do_parser (char *file_name) {
    md_token *tokens = malloc(sizeof(md_token) * MAX_TOKEN_SIZE);
    skip_space(file_name);
    md_token mt;
    FILE *f = fopen(MD_TMP_PATH, "r");
    process_line(file_name, f);
    process_sentence(file_name);
    pop_sentence(file_name);
}

