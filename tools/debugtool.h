/*
 * @Author: Zheng Qihang 
 * @Date: 2018-11-16 17:06:26 
 * @Last Modified by:   Zheng Qihang 
 * @Last Modified time: 2018-11-16 17:06:26 
 */
#ifndef __DEBUGTOOL_H
#define __DEBUGTOOL_H

#define DEBUG
/* clang-format off */
#ifdef DEBUG
#define dbg_print(fmt, ...) printf("\e[0;34m[DEBUG.] \e[0m"fmt, ##__VA_ARGS__)
// #define DEBUG(format,...) printf("FILE: "__FILE__", LINE: %d: "format"/n", __LINE__, ##__VA_ARGS__)
#endif
/* clang-format on */

#endif