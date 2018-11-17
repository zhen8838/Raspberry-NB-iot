/*
 * @Author: Zheng Qihang
 * @Date: 2018-11-16 17:06:20
 * @Last Modified by: Zheng Qihang
 * @Last Modified time: 2018-11-16 17:10:58
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct PrograssBar_S {
    int len;
    int delta;
    int cnt;
    char background;
    char foreground;
    char label[200];
    char *pbar;
};
/* @brief 全局变量用于保存参数
 *
 * */
static struct PrograssBar_S g_probar= {};
/* @brief 初始化
 * @ len          : 进度条长度
 * @ delta        : 进度条步进长度
 * @ background   : 进度条背景
 * @ foreground   : 进度条前景
 * @ label        : 进度条左侧图形  不可超过200!
 * */
void probar_init(int len, int delta, char backgroud, char foreground,
                 const char *label) {
    g_probar.cnt= 0;
    g_probar.len= len;
    g_probar.delta= delta;
    g_probar.background= backgroud;
    g_probar.foreground= foreground;
    char *pg_label= g_probar.label;
    for (const char *p= label; *p != '\0'; ++p) { *pg_label++= *p; }
    *pg_label= '\0';
    g_probar.pbar= (char *)malloc(sizeof(char) * g_probar.len);
    memset((void *)g_probar.pbar, 0x20, g_probar.len);
    printf("%s  [%-*s]   [%05.2f%%]   %s\r", g_probar.label, g_probar.len,
           g_probar.pbar, g_probar.cnt * (100 / (float)g_probar.len), "");
    fflush(stdout);
    g_probar.cnt++;
}

/* @brief 绘制进度条
 * @    show_str  : 用于描述进度
 *
 * */
void probar_show(const char *show_str) {
    if (g_probar.cnt == g_probar.len) { /* end */
        printf("%s  [%-*s]   [%05.2f%%]   %s\r", g_probar.label, g_probar.len,
               g_probar.pbar, g_probar.cnt * (100 / (float)g_probar.len), show_str);
        g_probar.cnt++;
        return;
    } else if (g_probar.cnt > g_probar.len) {
        return;
    }
    printf("%*c\r", 80, ' ');
    fflush(stdout);
    printf("%s  [%-*s]   [%05.2f%%]   %s\r", g_probar.label, g_probar.len,
           g_probar.pbar, g_probar.cnt * (100 / (float)g_probar.len), show_str);
    fflush(stdout);
    if (g_probar.cnt > 0) { g_probar.pbar[g_probar.cnt - 1]= g_probar.background; }
    g_probar.pbar[g_probar.cnt]= g_probar.foreground;
    g_probar.pbar[g_probar.cnt + 1]= '\0';
    g_probar.cnt++;
}

/* @brief 清空变量
 *
 * */
void probar_delete() {
    g_probar.cnt= 0;
    g_probar.len= 0;
    g_probar.delta= 0;
    g_probar.background= '=';
    g_probar.foreground= '>';
    free(g_probar.pbar);
    printf("%*c\r", 80, ' ');
    fflush(stdout);
}