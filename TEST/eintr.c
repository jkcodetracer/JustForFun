/*
 * @FileName: eintr.c
 * @Author: wzj
 * @Brief: 
 * 1.测试一下中断信号 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月09日星期一22:07:56
 * 
 */ 
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

void 
sig_handler(int sig_num)
{
	sig_num = sig_num;
	printf("...");
}


int 
main()
{
	int ret = 0;	

	signal(SIGCHLD, sig_handler);

	ret = pause();
	if(ret == -1 &&
		errno == EINTR)
	{
		printf("yes, you got it!\n");
	}

	return 0;
}
