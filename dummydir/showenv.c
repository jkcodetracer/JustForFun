/*
 * @FileName: showenv.c
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
 * @Date: 2012年04月26日星期四07:02:18
 * 
 */ 
#include <unistd.h>

int 
main(int argc, char* argv[], char* env[])
{
	int i = 0;

	while(1)
	{
		if(env[i] == NULL)
		{
			break;
		}
		
		printf("evn[%d]: %s\n", i, env[i]);
		i++;
	}

	return 0;
}
