#include <stdlib.h>
#include <markdown_token/markdown_token.h>
#include <markdown_sentence.h>
#include <markdown_paragraph.h>
#include <markdown_parser.h>

void do_parser (char *file_name) {
    char *tmp_name;
    FILE *f;
    tmp_name = tmpnam(NULL);
    f = fopen(tmp_name, "w+");
    if (!f) {
        exit(1);
    }
    skip_space(file_name, tmp_name);
    process_line(file_name, f);
    process_sentence(file_name, tmp_name);
    pop_sentence(file_name);
    fclose(f);
    remove(tmp_name);
}

