/*
 * @FileName: dup.c
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
 * @Date: 2012年05月20日星期日23:04:44
 * 
 */ 
#include <stdio.h>
#include <unistd.h>

int
main()
{
	int i = 5;

	dup2(1, 5);

	while(1)
	{
		write(5, "test", sizeof("test"));
		sleep(3);
	}

	return 0;
}
