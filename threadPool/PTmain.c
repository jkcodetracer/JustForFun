/*
 * @FileName: PTmain.c
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
 * @Date: 2011年12月11日星期日15:40:14
 * 
 */ 
#include"ThreadPool.h"
#include"Jlog.h"
#include<pthread.h>
#include<stdio.h>

void* PRINTT()
{
	printf("This is a test %d\n", 2);
}

int main()
{
	J_thread_pool* test_pool = create_thread_pool(10, 20);
	int i = 0;

	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			J_pool_deal_job(test_pool, PRINTT);			
		}
		sleep(5);
	}

	return 0;
}


