#include "hexstring.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************
 * 函数名称: *StringToByte
 * 说    明：字节转字符
 * 参    数: char *pString，需要转换的字符串
 *			unsigned char *pByte，转换之后的字节串
 * 返 回 值: 转换之后的字节串
 ***************************************************************/
unsigned char *StringToByte(char *pString, unsigned char *pByte) {
    unsigned int i, len= strlen(pString) / 2;
    char Hex[3]= {0};

    for (i= 0; i < len; i++) {
        memcpy(Hex, pString + 2 * i, 2);
        pByte[i]= strtol(Hex, NULL, 16);
    }
    return pByte;
}

/***************************************************************
 * 函数名称: *ByteToString
 * 说    明：字节转字符串
 * 参    数: unsigned char *pByte，需要转换的字节串
 *			char *pString，转换之后的字符串
 *			unsigned int len，len是转换之前string的长度
 * 返 回 值: 转换之后字符串
 ***************************************************************/
char *ByteToString(char *pByte, char *pString, unsigned int len) {
    unsigned int i;
    char a, b;
    for (i= 0; i < len; i++) {
        a= *(pByte + i) / 16;
        b= *(pByte + i) % 16;
        if (a <= 9 && b <= 9) {
            *(pString + i * 2)= a + '0';
            *(pString + i * 2 + 1)= b + '0';
        } else if (a <= 9 && b > 9) {
            *(pString + i * 2)= a + '0';
            *(pString + i * 2 + 1)= b - 10 + 'A';
        } else if (a > 9 && b <= 9) {
            *(pString + i * 2)= a - 10 + 'A';
            *(pString + i * 2 + 1)= b + '0';
        } else {
            *(pString + i * 2)= a - 10 + 'A';
            *(pString + i * 2 + 1)= b - 10 + 'A';
        }
    }
    *(pString + i * 2)= '\0';
    return pString;
}

/***************************************************************
 * 函数名称: *DecToString
 * 说    明：十进制数转字符串形式
 * 参    数: unsigned int Dec，需要转换的十进制数据
 *			char *pString，转换之后的字符串
 * 返 回 值: 转换之后字符串
 ***************************************************************/
char *DecToString(unsigned int Dec, char *pString) {
    unsigned char i= 0, j= 0;
    unsigned int Num;
    Num= Dec;
    while (Num >= 10) {
        Num/= 10;
        i++;
    }
    i++;
    while (i) {
        *(pString + j)= Dec / pow(10, i - 1) + '0';
        Dec%= (uint16_t)pow(10, i - 1);
        i--;
        j++;
    }
    *(pString + j)= '\0';
    return pString;
}

/* @brief 去除字符串左边的空字符
 *
 * */
char *lstrip(const char *str) {
    static char out[512]= {0};

    if (NULL == str) return NULL;

    const char *tmp= str;
    int start= 0;

    while (isspace(*tmp++)) start++;
    int len= strlen(str) - start;

    for (int i= 0; i <= len; ++i) { out[i]= *(str + i + start); }

    return out;
}

/* @brief 去除字符串右边的空字符
 *
 * */
char *rstrip(const char *str) {
    static char out[512]= {0};

    if (NULL == str) return NULL;
    const char *tmp= str;
    int len= strlen(str) - 1;

    while (isspace(*(str + len))) len--;

    for (int i= 0; i <= len + 1; ++i) { out[i]= *(str + i); }
    out[len + 2]= '\0';

    return out;
}

/* @brief 去除字符串两边的空字符
 *
 * */
char *strip(const char *str) {
    static char out[512]= {0};

    if (NULL == str) return NULL;

    const char *tmp= str;
    int len= strlen(str) - 1;
    int start= 0;

    while (isspace(*tmp++)) start++;
    while (isspace(*(str + len))) len--;

    for (int i= 0; i <= len - start + 1; ++i) { out[i]= *(str + start + i); }
    out[len - start + 2]= '\0';

    return out;
}

/* @brief 检查端口号与ip是否正确
 *      ip_prot 格式为 xxx.xxx.xxx.xxx:xxxx
 *      返回 1正确 0错误
 * */
int check_ip_port(const char *ip_port) {
    char server_ip[30]= {0};
    char ip_num[4][4];
    int num;
    char server_port[30]= {0};
    char *pos= strchr(ip_port, ':');
    char *lastdotpos= server_ip;
    char *dotpos= NULL;
    int dotlen= 0;
    if (pos == NULL || *(pos + 1) == '\0') { return 0; }
    strncpy(server_ip, ip_port, pos - ip_port);
    strcpy(server_port, pos + 1);
    for (int i= 0; i < 3; ++i) { //分三次截取ip中的数字
        dotpos= strchr(lastdotpos, '.');
        if (dotpos == NULL) { return 0; }
        strncpy(ip_num[i], lastdotpos, dotpos - lastdotpos);
        num= atoi(ip_num[i]);
        if (num < 0 || num > 255) { return 0; }
        // printf("ip_num :%d\n", num);
        lastdotpos= dotpos + 1;
    }
    //截取最后一个ip的数字
    strncpy(ip_num[3], lastdotpos, strlen(server_ip) - (lastdotpos - server_ip));
    num= atoi(ip_num[3]);
    if (num < 0 || num > 255) { return 0; }
    // printf("ip_num :%d\n", num);
    // 检查端口号是否错误
    num= atoi(server_port);
    // printf("prot :%d\n", num);
    if (num < 0 || num > 65535) { return 0; }
    return 1;
}