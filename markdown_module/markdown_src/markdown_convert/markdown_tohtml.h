

#ifndef HTTPSERV_MARKDOWN_TOHTML_H
#define HTTPSERV_MARKDOWN_TOHTML_H

#include "../markdown_config.h"

void produce_html_file (char *file, char *buf,bool init);

//此处<a>以及<href>标签的href需要额外的处理


#endif //HTTPSERV_MARKDOWN_TOHTML_H