#include <markdown_parser.h>
#include <markdown_config.h>
#include <markdown_html2pdf.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("ex: md_parser -f markdown.md -p {print pdf}? \n");
        return 1;
    }
    char file_name[64];
    bool is_printpdf = 0;
    int opt;
    while ((opt = getopt(argc, argv, "af:")) != -1) {
        switch (opt) {
            case 'a':
                is_printpdf = 1;
                break;
            case 'f':
                strcpy(file_name, optarg);
                break;
            default: {
                printf("ex: md_parser -f markdown.md -p {print pdf}? \n");
                return 1;
            }
        }
    }
    do_parser(file_name);
    if (is_printpdf) {
        convert_html2pdf(file_name);
    }
    return 0;
}
