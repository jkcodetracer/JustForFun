/*
 * @FileName: rcvChild.c
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
 * @Date: 2012年04月25日星期三22:13:06
 * 
 */ 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

int
main()
{
	int status, i;
	pid_t pid[4], retpid;

	for(i = 0; i < 4; i ++)
	{
		if((pid[i] = fork()) == 0)
		{
			sleep(10);
			exit(100 + i);
		}	
	}

	while((retpid = waitpid(pid[--i], &status, 0)) > 0)
	{
		if(WIFEXITED(status))
			printf("child %d terminated normally with  \
				%d\n", retpid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", retpid);
	}
	if(errno != ECHILD)
	{
		printf("waitpid error;\n");
	}

	return 0;
}
