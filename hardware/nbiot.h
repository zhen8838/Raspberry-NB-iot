#ifndef __NBIoT_H_
#define __NBIoT_H_

#include <stdint.h>

extern int NB_UART_FD;

/***************************************************************
 * 函数名称: NB_CONNRCT_STATUS
 * 说    明: 定义NB连接状态的结构体，供调用查看
 * 参    数: 无
 * 返 回 值: 无
 ***************************************************************/
typedef struct {
    uint8_t NB_ATTRACT_NET; // NB附着网络
} NB_CONNRCT_STATUS;

//-----------------------宏定义-------------------------------//
#define DefaultTimeout 1000 //默认超时时间1s

/**************************************************************/
/**************         NB接口        ***********************/
/**************************************************************/
extern int NB_SendCmd(char *cmd, char *result, uint32_t timeOut, uint8_t isPrintf);
extern int NB_SendCmd_Mul(char *cmd, char *result1, char *result2, uint32_t timeOut,
                          uint8_t isPrintf);
extern void NB_InitConnect(uint8_t isprintf);
extern void NB_SendMsgToServer(char *msg, uint8_t isprintf);
extern void NB_SetCDPServer(char *ncdpIP, char *port, uint8_t isprintf);
extern uint8_t NB_ReceiveMsg(char *msgReceive, uint8_t isprintf);
extern void *uart_read_th(void *arg);
extern void *nb_read_th(void *isprintf);
#endif
