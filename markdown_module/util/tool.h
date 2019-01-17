
#ifndef HTTPSERV_TOOL_H
#define HTTPSERV_TOOL_H
int hexit(char c);
void encode_str(char *to, int tosize, const char *from);
void decode_str(char *to, char *from);
const char *get_file_type(const char *name);
void write_log_file (char *content);
const char *get_datetime();
int get_hour();
int get_day();

#endif //HTTPSERV_TOOL_H
