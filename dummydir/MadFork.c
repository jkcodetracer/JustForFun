/*
 * @FileName: MadFork.c
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
 * @Date: 2012年04月25日星期三21:45:28
 * 
 */ 
#include <unistd.h>
#include <sys/types.h>

int 
main()
{
	int i = 0;

	for(; i < 3; i++)
	{
		if(fork() == 0)
		{
			printf("%d\n", i);
		}
	}

	while(1)
	{
		sleep(1);
	}

	return 0;
}
