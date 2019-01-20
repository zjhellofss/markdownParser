#include <stdlib.h>
#include <markdown_token/markdown_token.h>
#include <markdown_sentence.h>
#include <markdown_paragraph.h>

#if 0

void test () {
    md_token *tokens = malloc(sizeof(md_token) * MAX_TOKEN_SIZE);
    skip_space(MD_FILE_PATH);
    md_token mt;
    FILE *f = fopen(MD_TMP_PATH, "r");
    process_line(MD_FILE_PATH,f);
    process_sentence(MD_FILE_PATH);
    pop_sentence(MD_FILE_PATH);
}

int main () {
    test();
    int i;
    i++;
}

#endif