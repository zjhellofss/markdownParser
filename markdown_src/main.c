#include <markdown_parser.h>
#include <markdown_config.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("ex: md_parser markdown.md \n");
        return 1;
    }
    char *file_name = argv[1];
    do_parser(file_name);
    return 0;
}
