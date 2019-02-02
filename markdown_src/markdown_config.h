
#ifndef HTTPSERV_MARKDOWN_STRUCT_H
#define HTTPSERV_MARKDOWN_STRUCT_H
/*以 1. 2. 3. 符号构成的有序列表标记**/
#define  MD_UD_LIST 0x00
/*包括 '*' 以及 '-' 符号构成的无序列表标记 */
#define  MD_OD_LIST 0x01
/**删除线的标记*/
#define  MD_DEL    0x02
/**各级的head标签 标记*/
#define  MD_HEAD1  0x03
#define  MD_HEAD2  0x04
#define  MD_HEAD3  0x05
#define  MD_HEAD4  0x06
#define  MD_HEAD5  0x07
#define  MD_HEAD6  0x08
#define MD_HEAD7 0x09
/**斜体的标记*/
#define MD_ILY 0x0A
/**着重的标记*/
#define MD_IMPT 0x0B
/**小引用标记*/
#define MD_QUOTE_S 0x0C
/**大引用的标记*/
#define MD_QUOTE_L 0x0D
#define MD_PLAIN 0x0E
#define MD_LINK 0x0F
#define MD_IMG  0x10
#define MD_BLOCK 0x11
#define MD_LINE 0x12
#define MD_CHECKBOX 0x13
#define MD_HIGHLIGHT 0x14
#define MD_UNDER  0x15
#define MD_FORM 0x16
#define MD_FOOT 0x17
#define MD_RIGHT 0x18
typedef int MD_TYPE;
#define MD_MAX_STCE 8192
#define true 1
#define false 0
#define bool int
#endif //HTTPSERV_MARKDOWN_STRUCT_H
