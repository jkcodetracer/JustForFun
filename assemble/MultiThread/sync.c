/*
 * @FileName: sync.c
 * @Author: wzj
 * @Brief: 
 * 1.同步的东西 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月02日星期六07:32:01
 * 
 */ 
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NITERS 	(100000000)
void *count(void *arg);
unsigned int cnt = 0;

int
main()
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, count, NULL);
	pthread_create(&tid2, NULL, count, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(cnt != (unsigned)NITERS*2)
		printf("BOOM! cnt= %d\n", cnt);
	else
		printf("OK cnt=%d\n", cnt);
	
	return 0;
}

void*
count(void *arg)
{
	int i = 0;
	
	for(; i < NITERS; i++)
	{
		cnt ++;
	}

	return NULL;
}
