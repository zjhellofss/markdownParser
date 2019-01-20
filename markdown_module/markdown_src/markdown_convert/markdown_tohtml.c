#include "markdown_tohtml.h"
#include "../markdown_config.h"
#include <stdio.h>
#include <string.h>

void make_real_html (char *file) {
    char *file_;
    file_ = strchr(file, '.');
    char html_file[256] = {0};
    strncpy(html_file, file, file_ - file);
    strcpy(html_file + strlen(html_file), ".html");
    FILE *f2 = fopen(html_file, "w+");
    strcpy(html_file + strlen(html_file), ".tmp");
    FILE *f1 = fopen(html_file, "r");

    char c;
    while (fread(&c, 1, 1, f1)) {
        if ((int) c == 10) {
            c = '\n';
            fwrite(&c, 1, 1, f2);
        } else {
            fwrite(&c, 1, 1, f2);
        }
    }
    fclose(f1);
    fclose(f2);
    /*删除临时文件*/
    remove(html_file);
}

void produce_tmp_html_file (char *file, char *buf, bool init) {
    char *file_;
    file_ = strchr(file, '.');
    char html_file[256] = {0};
    strncpy(html_file, file, file_ - file);
    strcpy(html_file + strlen(html_file), ".html.tmp");
    FILE *f = fopen(html_file, "a+");
    if (!f) {
        return;
    }
    if (!init) {
        fwrite(buf, sizeof(char), strlen(buf), f);
    } else {
        char buf1[1024] = {0};
        strcpy(buf1, "<!DOCTYPE html>\n"
                     "<html>\n"
                     "<head>\n"
                     "    <meta charse=\"utf-8\">\n"
                     "    <title>");
        strcpy(buf1 + strlen(buf1), file);
        strcpy(buf1 + strlen(buf1),
               "</title><link rel=\"stylesheet\" href=\"https://cdn.staticfile.org/twitter-bootstrap/3.3.7/css/bootstrap.min.css\">\n"
               "    <script src=\"https://cdn.staticfile.org/jquery/2.1.1/jquery.min.js\"></script>\n"
               "    <script src=\"https://cdn.staticfile.org/twitter-bootstrap/3.3.7/js/bootstrap.min.js\"></script>\n"
               "\n"
               "    <link rel=\"stylesheet\" href=\"../markdown_src/markdown_htmlcss/github.css\">\n"
               "    <script src=\"../markdown_src/markdown_htmlcss/highlight.pack.js\"></script>\n"
               "    <script>\n"
               "        hljs.initHighlightingOnLoad();\n"
               "    </script>\n"
               "</head>");
        fwrite(buf1, sizeof(char), strlen(buf1), f);
    }
    fclose(f);
}

