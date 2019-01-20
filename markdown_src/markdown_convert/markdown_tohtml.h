

#ifndef HTTPSERV_MARKDOWN_TOHTML_H
#define HTTPSERV_MARKDOWN_TOHTML_H

#include "../markdown_config.h"

void produce_tmp_html_file (char *file, char *buf, bool init);

void make_real_html (char *file);

//此处<a>以及<href>标签的href需要额外的处理
void remove_tmp_html_file (char *);


#endif //HTTPSERV_MARKDOWN_TOHTML_H
