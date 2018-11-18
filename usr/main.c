/*
 * @Author: Zheng Qihang
 * @Date: 2018-11-08 20:34:00
 * @Last Modified by: Zheng Qihang
 * @Last Modified time: 2018-11-17 23:37:43
 */
/* c std lib header file */
#include "main.h"
#include "color.h"
#include "hexstring.h"
#include "nbiot.h"
#include "uart.h"
void usage_error(const char *s) {
    printf(YELLOW "Usage :" NONE "%s [-p -b -s -h ]\n \
    -p  tty port  default:\"/dev/ttyUSB0\" \n \
    -b  baud rate default:\"9600\" \n \
    -s  set the server ip and port  default:\"180.101.147.115:5683\" \n \
    -h  display help \n \
    -v  verbose mode \n \
    when start program you can : \n \
    press 'c'	设置CDP服务器（IoT平台）的IP和端口号    \n \
    press 's'	按下按键2发送数据到服务器    \n \
    press 'h'	获取帮助  \n \
    press 'q'	退出本程序  \n",
           s);
    exit(-1);
}

void config_print(const char *port, int rate, const char *ip, const char *s_port) {
    printf(VERBOSE_C "Now Config is : \n \
    tty_port    : %s\n \
    baud_rate   : %d\n \
    server_ip   : %s\n \
    server_port : %s\n",
           port, rate, ip, s_port);
}
void opt_print(void) {
    printf(YELLOW "帮助:" NONE " \n \
输入 'c'	设置CDP服务器（IoT平台）的IP和端口号    \n \
输入 's'	按下按键2发送数据到服务器    \n \
输入 'h'	获取帮助  \n \
输入 'q'	退出本程序  \n");
}
/* @brief  读取cpu温度
 *
 * */
float get_cpu_temp(void) {
    uint32_t temp;
#ifdef __amd64
    FILE *fp= fopen("/sys/class/thermal/thermal_zone0/temp", "r");
#endif
#ifdef __arm__
    FILE *fp= fopen("/sys/class/thermal/thermal_zone0/temp", "r");
#endif
    fscanf(fp, "%u", &temp);
    fclose(fp);
    return temp / 1000.0;
}
/* @brief  read the mem usage
 *
 * */
float get_mem_use(void) {
    struct sysinfo si;
    sysinfo(&si);
    float total= (double)si.totalram / 1024 / 1024;
    float freeram= (double)si.freeram / 1024 / 1024;
    return ((total - freeram) / total) * 100;
}

int main(int argc, char *argv[]) {
    char msgSend[9]= {0};
    int optch;
    int ret= -1;
    char nb_tty_port[30]= "/dev/ttyUSB0";
    char server_ip[30]= "180.101.147.115";
    char server_port[30]= "5683";
    int baud_rate= 9600;
    bool verbose_mode= false;
    pthread_t th_uart_rx= -1, nb_read_msg= -1;
    if (argc > 1) {
        while ((optch= getopt(argc, argv, "p:b:s:hv")) != -1) {
            switch (optch) {
            case 'p':
                strcpy(nb_tty_port, optarg);
                break;
            case 'b':
                baud_rate= atoi(optarg);
                break;
            case 's': {
                if (!check_ip_port(optarg)) {
                    printf(ERROR_C "IP or Port, Please check ip and prot: \"%s\"\n",
                           optarg);
                    exit(-1);
                } else {
                    char *pos= strchr(optarg, ':');
                    memset(server_ip, 0, strlen(server_ip));
                    memset(server_port, 0, strlen(server_port));
                    strncpy(server_ip, optarg, pos - optarg);
                    strcpy(server_port, pos + 1);
                }
            } break;
            case 'h':
                usage_error(argv[0]);
                break;
            case 'v':
                verbose_mode= true;
                break;
            default:
                usage_error(argv[0]);
                break;
            }
        }
    }
    config_print(nb_tty_port, baud_rate, server_ip, server_port);
    ret= UART_Open(&NB_UART_FD, nb_tty_port);
    if (ret < 0) {
        printf(ERROR_C "Uart Open, Please check the port : \"%s\"\n", nb_tty_port);
        exit(-1);
    }
    ret= UART_Init(NB_UART_FD, baud_rate, 0, 8, 1, 'N');
    if (ret == 0) {
        printf(OK_C "Uart Init\n");
    } else {
        printf(ERROR_C "Uart Init, Please check the port : \"%s\"\n", nb_tty_port);
        exit(-1);
    }
    /* start the thread */
    if ((ret= pthread_create(&th_uart_rx, NULL, uart_read_th, NULL)) != 0) {
        printf(ERROR_C "Thread Create,code %d \n", ret);
    }
    /* connect nb */
    NB_InitConnect(verbose_mode);
    printf(OK_C "NB Init success!\n");
    opt_print();
    while (1) {
        char c= getchar();
        switch (c) {
        case 'c': // 连接服务器
            NB_SetCDPServer("180.101.147.115", "5683", verbose_mode);
            printf(OK_C "NB Connect success!\n");
            // start the nb msg recive thread
            /* clang-format off */
            ret= pthread_create(&nb_read_msg, NULL, nb_read_th, (void *)&verbose_mode);
            /* clang-format on */
            if (ret != 0) {
                printf(ERROR_C "Thread2 Create,code %d\n", ret);
            } else {
                printf(OK_C "NET Msg Start listening \n");
            }
            break;
        case 's': {
            // 读取温湿度数据并发送
            char wendu[10]= {0};
            sprintf(wendu, "%.1f%.1f", get_cpu_temp(), get_mem_use());
            ByteToString(wendu, msgSend, 8);
            NB_SendMsgToServer(msgSend, verbose_mode);
            printf(OK_C "Send Success!\n");
        } break;
        case 'h': // 打印帮助
            opt_print();
            break;
        case 'q': // 退出程序
            printf(OK_C "Good Bye ~\n");
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
