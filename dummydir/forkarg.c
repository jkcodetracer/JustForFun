/*
 * @FileName: dummy.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年04月26日星期四06:38:15
 * 
 */ 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int k = 15;
int g_run = 1;

void 
signal_handler(int arg)
{
	printf("....\n");
	g_run = 0;
	return;
}

int 
main()
{
	int i = 0;
	pid_t pid = 0;
	char* test = NULL;

	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
//	signal(SIGINT, SIG_IGN);

	test = malloc(16);
	memset(test, 0, 16);

	pid = fork();
	if(pid == 0)
	{
		while(g_run)
		{
			sprintf(test, "what..");
			printf("child:%d, k = %d g:%d\n", getpid(), k--, g_run);
			printf("chile:%s\n", test);
			sleep(1);
		}
	} else {
		while(g_run)
		{
			sprintf(test, "fuction...");
			printf("father:%d, k = %d g:%d\n", getpid(), k++, g_run);	
			printf("father:%s\n", test);
			sleep(1);
		}
	}

	free(test);

	return 0;
}
