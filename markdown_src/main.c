#include <markdown_parser.h>
#include <markdown_config.h>
#include <markdown_html2pdf.h>
#include <markdown_translate/markdown_translate.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("ex: md_parser -f markdown.md -a {need print pdf?}? -n {delay to load js in html?} \n");
        return 1;
    }
    char file_name[64];
    bool is_printpdf = false;
    bool is_delay = false;
    int opt;
    while ((opt = getopt(argc, argv, "anf:")) != -1) {
        switch (opt) {
            case 'a':
                is_printpdf = true;
                break;
            case 'f':
                strcpy(file_name, optarg);
                break;
            case 'n':
                is_delay = true;
                break;
            default: {
                printf("ex: md_parser -f markdown.md -a {need print pdf?}? -n {delay to load js in html?} \n");
                return 1;
            }
        }
    }
    do_parser(file_name);
    if (is_printpdf) {
        printf("正在输出为pdf,请稍后...\n");
        convert_html2pdf(file_name, is_delay);
        printf("pdf生成完毕...\n");
    }
    return 0;
}
