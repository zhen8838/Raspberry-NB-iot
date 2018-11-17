/*
 * @Author: Zheng Qihang
 * @Date: 2018-08-08 12:38:17
 * @Last Modified by: Zheng Qihang
 * @Last Modified time: 2018-11-08 21:45:21
 */
#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#define UART_PORT0 "/dev/ttyS0"
#define UART_PORT1 "/dev/ttyS1"
#define UART_PORT2 "/dev/ttyS2"

extern int UART_Open(int *fd, const char *port);
extern void UART_Close(int fd);
extern int UART_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits,
                    int parity);
extern int UART_Init(int fd, int speed, int flow_ctrl, int databits, int stopbits,
                     int parity);
extern int UART_Recv(int fd, char *rcv_buf, int data_len, int wait_s, int wait_us);
extern int UART_Send(int fd, const char *send_buf, int data_len);

#ifdef __cplusplus
}
#endif

#endif // _UART_H_
