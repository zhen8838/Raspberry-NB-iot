/*
 * @Author: Zheng Qihang 
 * @Date: 2018-11-16 17:06:28 
 * @Last Modified by:   Zheng Qihang 
 * @Last Modified time: 2018-11-16 17:06:28 
 */
#ifndef __COLOR_H_
#define __COLOR_H_

/* clang-format off */
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K"

#define ERROR_C              "\e[0;31m[  ERR   ] \e[0m" 
#define OK_C                 "\e[0;32m[   OK   ] \e[0m"
#define DEBUG_C              "\e[0;34m[ DEBUG  ] \e[0m"
#define VERBOSE_C            "\e[0;35m[ DETAIL ] \e[0m"
#define WAIT_C               "\e[0;33m[  WAIT  ] \e[0m"
/* clang-format on */

#endif