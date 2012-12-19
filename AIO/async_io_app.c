/**
 * \file async_io_app.c
 * \author  wzj
 * \brief 
 	异步IO， 通过驱动发送信号来通知应用层可以进行I/O
 * \version 
 * \note  
 * \date: 2012年10月01日星期一23:15:11
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_LEN 100

int fd;

void sig_handler(int signum)
{
	char data[MAX_LEN];
	int len;
		
	len = read(fd, data, MAX_LEN);
	data[len] = 0;
	
	printf("input frome driver: [%s]\n", data);
}

int main(int argc, char *argv[])
{
	int flags;
	
	fd = open("/dev/cdev_aio", O_RDWR, S_IRUSR | S_IWUSR);
	if(fd < 0)
	{
		printf("Device Open failed!\n");
		return -1;
	}

	signal(SIGIO, sig_handler);
	/* 如果不设定描述符的所有者，不可能获取到信号 */
	fcntl(fd, F_SETOWN, getpid());	
	/* 设置设备文件支持O_ASYNC/FASYNC模式， 即异步通知模式 */
	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | O_ASYNC);

	while(1)
		sleep(5);
	
	return 0;
}




