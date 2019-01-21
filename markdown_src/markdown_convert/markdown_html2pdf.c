#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void convert_html2pdf (const char *filename) {
    char *command = malloc(512);
    char *filename_prefix_h = malloc(sizeof(char) * 128);
    memset(filename_prefix_h, '\0', 128);
    char *file_ = strchr(filename, '.');
    strncpy(filename_prefix_h, filename, file_ - filename);
    strcpy(filename_prefix_h + strlen(filename_prefix_h), ".html");

    char *filename_prefix = malloc(sizeof(char) * 128);
    memset(filename_prefix, '\0', 128);
    strncpy(filename_prefix, filename, file_ - filename);
    strcpy(filename_prefix + strlen(filename_prefix), ".pdf");
    sprintf(command, "%s %s %s %s", "wkhtmltopdf", "--footer-font-name 'Menlo' --footer-right [page] --encoding utf-8 --no-stop-slow-scripts --javascript-delay 2500 ", filename_prefix_h, filename_prefix);
    system(command);
    free(filename_prefix);
    free(filename_prefix_h);
    free(command);
}