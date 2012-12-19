/*
 * @FileName: test.c
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
 * @Date: 2012年06月28日星期四22:43:29
 * 
 */ 
#include <stdio.h>

int
main()
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		printf("My counter: %d\n", i);
		sleep(2);
	}

	return 0;
}
