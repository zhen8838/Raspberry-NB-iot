# Raspberry-NB-iot
树莓派3B使用NB-iot,上传cpu温度以及内存使用率.

Raspberry 3B use NB-iot,update the cpu temperature and memory utilization rate.

**注:** 本程序暂时只支持[物联网俱乐部NB-iot开发板](https://item.taobao.com/item.htm?spm=a230r.1.14.130.293c66c4POneaH&id=576818997326&ns=1&abbucket=7#detail)


# 安装

**注:** 请先安装`cmake`与`git`:
```sh
sudo apt-get install cmake git
```
执行:
```sh
git clone https://github.com/zhen8838/Raspberry-NB-iot.git
cd Raspberry-NB-iot 
mkdir build && cd build
cmake ..     
make
```

# 使用

获取帮助:

```sh
./RaspNB -h
Usage :././RaspNB [-p -b -s -h ]
     -p  tty port  default:"/dev/ttyUSB0"
     -b  baud rate default:"9600"
     -s  set the server ip and port  default:"180.101.147.115:5683"
     -h  display help
     -v  verbose mode
     when start program you can :
     press 'c'  设置CDP服务器（IoT平台）的IP和端口号
     press 's'  按下按键2发送数据到服务器
     press 'h'  获取帮助
     press 'q'  退出本程序
```

指定各项参数

```
./RaspNB -p /dev/ttyUSB1 -b 9600 -s 101.0.4.88:5683 -v
```


# 截图

![示例](screenshot.png)