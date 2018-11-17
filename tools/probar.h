/*
 * @Author: Zheng Qihang 
 * @Date: 2018-11-16 17:06:22 
 * @Last Modified by:   Zheng Qihang 
 * @Last Modified time: 2018-11-16 17:06:22 
 */
#ifndef __PROBAR_H
#define __PROBAR_H

extern void probar_init(int len, int delta, char backgroud, char foreground,
                        const char *label);
extern void probar_delete();
extern void probar_show(const char *show_str);

#endif