/*
 * @FileName: multi_signal.c
 * @Author: wzj
 * @Brief: 
 *  1. 悲剧的信号处理，后面的都被舍弃了，僵尸现身！ 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年04月30日星期一10:11:54
 * 
 */ 
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define MAXBUF (1024)

void
handler(int sig)
{
	pid_t pid;
	
	if((pid = waitpid(-1, NULL, 0)) < 0)
	{
		printf("waitpid error");
	}

	printf("handler child exit %d\n", (int) pid);
	sleep(2);
	return;
}

int
main(int argc, char* argv[])
{
	int i, n;
	char buf[MAXBUF];
	
	if(signal(SIGCHLD, handler) == SIG_ERR)
	{
		printf("signal error");
		return -1;
	}
	
	for(i = 0; i < 3; i++)	
	{
		if(fork() == 0)
		{
			printf("child %d\n", (int)getpid());
			sleep(1);
			exit(0);
		}
	}

	if((n = read(0, buf, sizeof(buf))) < 0)
	{
		printf("error read");
		return -1;
	}

	while(1)

	return 0;
}

