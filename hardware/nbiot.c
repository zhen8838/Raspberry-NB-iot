/*
 * @Author: Zheng Qihang
 * @Date: 2018-11-16 11:53:49
 * @Last Modified by: Zheng Qihang
 * @Last Modified time: 2018-11-16 19:45:04
 */
#include "nbiot.h"
#include "color.h"
#include "debugtool.h"
#include "hexstring.h"
#include "probar.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/***************************************************************
 * 文件名称: nbiot
 * 作    者: 物联网俱乐部
 * 版    本: V1.0
 * 编写日期: 2018-10-1
 * 功    能: NB数据收发
 ****************************************************************
 * 硬件平台: 本例程配套物联网俱乐部EVB_M1开发板使用
 * 淘    宝: iot-club.taobao.com、https://shop449662000.taobao.com
 * 论    坛: www.iot-club.cn 、bbs.iot-club.cn
 ****************************************************************/
char cmdSend[512];
volatile char UART_RX_BUF[512];
volatile uint16_t UART_RX_LEN= 0;
int NB_UART_FD= -1;
char msgReceive[512]= {0};
/***************************************************************
 * 函数名称: NB_SendCmd
 * 说    明: NB发送数据
 * 参    数: uint8_t *cmd，需要发送的命令
 *			uint8_t *result，期望获得的结果
 *			uint32_t timeOut，等待期望结果的时间
 *			uint8_t isPrintf，是否打印Log
 * 返 回 值: ret，返回值
 ***************************************************************/
int NB_SendCmd(char *cmd, char *result, uint32_t timeOut, uint8_t isPrintf) {
    int ret= 0;
    memset((void *)UART_RX_BUF, 0, strlen((const char *)UART_RX_BUF)); //清除缓存
    if (isPrintf) { printf(VERBOSE_C "MCU-->>NB: %s\n", rstrip((const char *)cmd)); }
    UART_Send(NB_UART_FD, cmd, strlen(cmd));
    usleep(1000 * 500);
    while (1) {
        if (strstr((const char *)UART_RX_BUF, (const char *)result)) {
            ret= 0;
            break;
        } else {
            if (isPrintf) {
                printf(VERBOSE_C "MCU-->>NB: %s\n", rstrip((const char *)cmd));
            }
            UART_Send(NB_UART_FD, cmd, strlen(cmd));
            UART_RX_LEN= 0;
            usleep(1000 * timeOut);
        }
    }
    if (isPrintf) {
        printf(VERBOSE_C "NB-->>MCU: %s\n", strip((const char *)UART_RX_BUF));
    }
    usleep(1000 * timeOut);
    UART_RX_LEN= 0;
    return ret;
}

/***************************************************************
 * 函数名称: NB_SendCmd_Mul
 * 说    明: NB发送数据，返回值有多个
 * 参    数: uint8_t *cmd，需要发送的命令
 *						uint8_t *result，期望获得的结果1
 *						uint8_t *result，期望获得的结果2
 *						uint32_t timeOut，等待期望结果的时间
 *						uint8_t isPrintf，是否打印Log
 * 返 回 值: ret，返回值
 ***************************************************************/
int NB_SendCmd_Mul(char *cmd, char *result1, char *result2, uint32_t timeOut,
                   uint8_t isPrintf) {
    int ret= 0;
    memset((void *)UART_RX_BUF, 0, strlen((const char *)UART_RX_BUF)); //清除缓存
    if (isPrintf) { printf(VERBOSE_C "MCU-->>NB: %s\n", rstrip((const char *)cmd)); }
    UART_Send(NB_UART_FD, cmd, strlen(cmd));
    usleep(1000 * 100);
    while (1) {
        if (strstr((const char *)UART_RX_BUF, (const char *)result1) ||
            strstr((const char *)UART_RX_BUF, (const char *)result2)) {
            ret= 0;
            break;
        } else {
            if (isPrintf) {
                printf(VERBOSE_C "MCU-->>NB: %s\n", rstrip((const char *)cmd));
            }
            UART_Send(NB_UART_FD, cmd, strlen(cmd));
            usleep(1000 * timeOut);
        }
    }
    if (isPrintf) {
        printf(VERBOSE_C "NB-->>MCU: %s\n", strip((const char *)UART_RX_BUF));
    }
    usleep(1000 * timeOut);
    UART_RX_LEN= 0;
    return ret;
}

/***************************************************************
 * 函数名称: NB_InitConnect
 * 说    明: NB初始化入网过程
 * 参    数: isprint 1: 打印输出 0:不打印输出
 * 返 回 值: 无
 ***************************************************************/
void NB_InitConnect(uint8_t isprintf) {
    if (!isprintf) {
        probar_init(11, 1, '=', '>', WAIT_C);
        NB_SendCmd("AT+CFUN?\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CFUN?");
        NB_SendCmd("AT+CGSN=1\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CGSN=1");
        NB_SendCmd("AT+CIMI\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CIMI");
        NB_SendCmd("AT+CGATT=1\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CGATT=1");
        NB_SendCmd("AT+CGATT?\r\n", "+CGATT:1", DefaultTimeout, isprintf);
        probar_show("AT+CGATT?");
        NB_SendCmd("AT+CSQ\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CSQ");
        NB_SendCmd("AT+COPS?\r\n", "+COPS:0,2,\"46011\"", DefaultTimeout, isprintf);
        probar_show("AT+COPS?");
        NB_SendCmd("AT+CEREG=1\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+CEREG=1");
        NB_SendCmd("AT+CEREG?\r\n", "+CEREG:1,1", DefaultTimeout, isprintf);
        probar_show("AT+CEREG?");
        NB_SendCmd("AT+NNMI=1\r\n", "OK", DefaultTimeout, isprintf);
        probar_show("AT+NNMI=1");
        NB_SendCmd("AT+NNMI?\r\n", "+NNMI:1", DefaultTimeout, isprintf);
        probar_show("AT+NNMI?");
        probar_delete();
    } else {
        NB_SendCmd("AT+CFUN?\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CGSN=1\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CIMI\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CGATT=1\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CGATT?\r\n", "+CGATT:1", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CSQ\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+COPS?\r\n", "+COPS:0,2,\"46011\"", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CEREG=1\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+CEREG?\r\n", "+CEREG:1,1", DefaultTimeout, isprintf);
        NB_SendCmd("AT+NNMI=1\r\n", "OK", DefaultTimeout, isprintf);
        NB_SendCmd("AT+NNMI?\r\n", "+NNMI:1", DefaultTimeout, isprintf);
    }
}

/***************************************************************
 * 函数名称: NB_SendMsgToServer
 * 说    明: NB发送消息到服务器
 * 参    数: *msg，要发送的数据（String形式）, isprintf 是否输出
 * 返 回 值: 无
 ***************************************************************/
void NB_SendMsgToServer(char *msg, uint8_t isprintf) {
    //例：AT+NMGS=len,msg
    memset(cmdSend, 0, sizeof(cmdSend));
    uint8_t len= 0;
    char msgLen[4]= {0};
    len= strlen((const char *)msg) / 2;
    DecToString(len, msgLen);
    strcat(cmdSend, "AT+NMGS=");
    strcat(cmdSend, msgLen);
    strcat(cmdSend, ",");
    strcat(cmdSend, (const char *)msg);
    strcat(cmdSend, "\r\n");
    NB_SendCmd(cmdSend, "OK", DefaultTimeout, isprintf);
}
/***************************************************************
 * 函数名称: NB_SetCDPServer
 * 说    明: NB设置CDP服务器
 * 参    数: *ncdpIP，要发送的服务器（平台）的IP地址
 *			*port，要发送的服务器（平台）的端口号
 * 返 回 值: 无
 ***************************************************************/
void NB_SetCDPServer(char *ncdpIP, char *port, uint8_t isprintf) {
    //例：AT+NCDP=ncdpIP,port
    memset(cmdSend, 0, sizeof(cmdSend));
    strcat(cmdSend, "AT+NCDP=");
    strcat(cmdSend, (const char *)ncdpIP);
    strcat(cmdSend, ",");
    strcat(cmdSend, (const char *)port);
    strcat(cmdSend, "\r\n");
    NB_SendCmd(cmdSend, "OK", DefaultTimeout, isprintf);
}

/***************************************************************
 * 函数名称: NB_ReceiveMsg
 * 说    明: NB从服务器接收数据
 * 参    数: msgReceive,NB接收到的数据,该参数传入时请先分配好内存空间
 * 返 回 值: SUCCESS，接收成功
 *			ERROR，接收失败或无接收数据
 ***************************************************************/
uint8_t NB_ReceiveMsg(char *msgReceive, uint8_t isprintf) {
    //例：+NNMI:2,4F4E
    char *pos1, *pos3;
    pos1= strstr((char *)UART_RX_BUF, "+NNMI:");
    if (pos1) {
        usleep(1000 * 500);
        char *pos2;
        uint8_t msgReceiveLen;
        msgReceiveLen= atoi(pos1 + 6);
        if (isprintf) {
            printf(VERBOSE_C "NET-->>NB: %s \n", strip((const char *)UART_RX_BUF));
        }
        pos2= strstr((char *)UART_RX_BUF, ",");
        memcpy(msgReceive, pos2 + 1,
               msgReceiveLen * 2); // pos2指向的是“,”  pos2+1指向的是数据
        memset((void *)UART_RX_BUF, 0, UART_RX_LEN);
        UART_RX_LEN= 0;
        return 1;
    }
    pos3= strstr((char *)UART_RX_BUF, "+NSONMI:0");
    if (pos3) {
        usleep(1000 * 500);
        char *recvBuf;
        char msg[20]= {0};
        if (isprintf) {
            printf(VERBOSE_C "NET-->>NB: %s \n", strip((const char *)UART_RX_BUF));
        }
        strcat(msg, "AT+NSORF=0,");
        UART_RX_LEN= atoi(pos3 + 10); //获取要接收数据的长度
        // printf("UART_RX_BUF_LEN: %d \n", UART_RX_LEN);
        recvBuf= (char *)malloc(sizeof(uint8_t) * UART_RX_LEN * 2);
        memset(recvBuf, 0, UART_RX_LEN * 2);
        DecToString(UART_RX_LEN, &msg[strlen(msg)]); // AT指令拼接
        strcat(msg, "\r\n");
        memset((void *)UART_RX_BUF, 0, strlen((const char *)UART_RX_BUF));
        UART_RX_LEN= 0;
        //发送取数据指令
        UART_Send(NB_UART_FD, msg, strlen(msg));
        while (NULL != strstr((const char *)UART_RX_BUF, ",5683,")) {}; //接收到数据
        usleep(1000 * 200); //为了能够完全接收到所有数据
        // printf("NB DATA RECEIVE: %s \n", strip((const char *)UART_RX_BUF));
        recvBuf= strtok((char *)UART_RX_BUF, ","); // AT+NSORF=0
        recvBuf= strtok(NULL, ",");                //切掉线程号
        //		printf("线程号: %s \r\n",recvBuf);
        ////打印的线程号数据前面是AT+NSORF=0后面的长度及回车换行
        recvBuf= strtok(NULL, ","); //切掉IP地址
                                    // printf("IP地址: %s \r\n",recvBuf);
        recvBuf= strtok(NULL, ","); //切掉端口号
                                    // printf("端口号: %s \r\n",recvBuf);
        //切掉message长度
        recvBuf= strtok(NULL, ",");
        // printf("message长度: %s \r\n",recvBuf);
        recvBuf= strtok(NULL, ","); //返回message
        if (isprintf) { printf(VERBOSE_C "NB Msg Receive: %s\n", strip(recvBuf)); }
        memcpy(msgReceive, recvBuf, UART_RX_LEN * 2);
        free(recvBuf);
        recvBuf= NULL;
        memset((void *)UART_RX_BUF, 0, UART_RX_LEN);
        UART_RX_LEN= 0;
        return 1;
    }
    return 0;
}

/* @brief 读取串口数据线程
 *
 * */
void *uart_read_th(void *arg) {
    int read_buf_len= 0;
    char read_buf_tmp[32]= {0};
    while (1) { //读取串口数据
        read_buf_len= UART_Recv(NB_UART_FD, read_buf_tmp, 32, 10, 0);
        if (read_buf_len > 0) {
            if ((UART_RX_LEN + read_buf_len) < 512) {
                for (int i= 0; i < read_buf_len; ++i) {
                    UART_RX_BUF[i + UART_RX_LEN]= read_buf_tmp[i];
                }
            }
            UART_RX_LEN+= read_buf_len;
        }
    }
}

/* @brief 解析串口数据查看有无平台发送信息
 *   数据下发前的30s内需要有数据上报
 *
 * */
void *nb_read_th(void *isprintf) {
    while (1) {
        usleep(1000 * 1000);
        if (NB_ReceiveMsg(msgReceive, *((uint8_t *)isprintf)) == 1) {
            printf(OK_C "NB Msg Receive: %s\n", strip(msgReceive));
        }
    }
    return NULL;
}
