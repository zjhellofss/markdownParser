#include "markdown_translate.h"
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include "cJSON.h"

static size_t write_back (void *contents, size_t size, size_t nmemb, void *userp) {

    size_t realsize = size * nmemb;
    struct memory_struct *mem = (struct memory_struct *) userp;
    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (!mem->memory) {
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;

}

/**
* 这烂代码百度写的，我实在看不下去
*
* @param query  需要翻译查询的字串
*/
char *markdown_passage_translate_ (char *q) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (!curl) {
        return NULL;
    }
    char *es_q = curl_escape(q, (int) strlen(q));
    char myurl[16384] = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
    char *appid = "20160517000021280";
    char *from = "auto";
    char *to = "zh";
    char salt[60];
    srand((unsigned) time(NULL));
    int a = rand();
    sprintf(salt, "%d", a);
    char *secret_key = "NxJF4bJA97zbnwwrBN5_";
    char sign[16384] = {0};
    strcat(sign, appid);
    strcat(sign, q);
    strcat(sign, salt);
    strcat(sign, secret_key);
    unsigned char md[16];
    int i;
    char tmp[3] = {'\0'}, buf[33] = {'\0'};
    MD5((unsigned char *) sign, strlen((unsigned char *) sign), md);
    for (i = 0; i < 16; i++) {
        sprintf(tmp, "%2.2x", md[i]);
        strcat(buf, tmp);
    }
    strcat(myurl, "appid=");
    strcat(myurl, appid);
    strcat(myurl, "&q=");
    strcat(myurl, es_q);
    strcat(myurl, "&from=");
    strcat(myurl, from);
    strcat(myurl, "&to=");
    strcat(myurl, to);
    strcat(myurl, "&salt=");
    strcat(myurl, salt);
    strcat(myurl, "&sign=");
    strcat(myurl, buf);
    struct memory_struct chunk;
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
    curl_easy_setopt(curl, CURLOPT_URL, myurl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_back);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
    res = curl_easy_perform(curl);
    char *rs_str = chunk.memory;
    if (res != CURLE_OK)
        fprintf(stderr, "翻译访问失败: %s\n",
                curl_easy_strerror(res));
    curl_easy_cleanup(curl);
    return rs_str;
}


void init_res_node_list (struct res_node_list *l) {
    l->d_len = 0;
    l->s_len = 0;
}


void insert_res_node_list (struct res_node_list *l, char *str, STYPE type) {
    size_t len = strlen(str);
    if (type == SNODE) {
        struct ttstr_src_node n;
        n.str = malloc(sizeof(char) * len+2);
        memset(n.str, '\0', len);
        strcpy(n.str, str);
        l->ts_src_lists[l->s_len++] = n;
    } else if (type == DNODE) {
        struct ttstr_dst_node n1;
        n1.str = malloc(sizeof(char) * len+2);
        memset(n1.str, '\0', len);
        strcpy(n1.str, str);
        l->ts_dst_lists[l->d_len++] = n1;
    } else {
        printf("程序异常\n");
        fflush(stdout);
        exit(0);
    }
}

struct res_node_list *markdown_passage_translate (char *qstr) {
    struct res_node_list *l = malloc(sizeof(struct res_node_list));
    init_res_node_list(l);
    char *json_str = markdown_passage_translate_(qstr);
    cJSON *ts_json = cJSON_Parse(json_str);
    cJSON *res = cJSON_GetObjectItem(ts_json, "trans_result");
    if (res != NULL) {
        if (res->type == cJSON_Array) {
            for (int i = 0; i < cJSON_GetArraySize(res); ++i) {
                cJSON *d_node = cJSON_GetArrayItem(res, i);
                cJSON *dst = cJSON_GetObjectItem(d_node, "dst");
                cJSON *src = cJSON_GetObjectItem(d_node, "src");
                if (dst) {
                    insert_res_node_list(l, dst->valuestring, DNODE);
                    dst = NULL;
                }
                if (src) {
                    insert_res_node_list(l, src->valuestring, SNODE);
                    src = NULL;
                }
            }
        }
    } else {
        printf("翻译返回结果异常\n");
        fflush(stdout);
        exit(1);
    }
    return l;
}

