/**
 * \file main.c
 * \author  wzj
 * \brief 
 *	test the kebab api...
 * \version 
 * \note  
 * \date: 2013年07月21日星期日22:10:43
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>

#include <Jlog.h>
#include "kebab.h"

void* func_b(kebab_sched_st *psched, void *arg)
{
	int i = 0;
	int n = (int)arg;

	while(i < n) {
		printf("func_b: step[%d]\n", i);	
		i++;
		kebab_yield(psched);
	}

	return NULL;
}

void* func_a(kebab_sched_st *psched, void *arg)
{
	int i = 0;
	int n = (int)arg;
	printf("go again..\n");

	while(i < n) {
		dblog("addr: %p\n", &n);
		printf("func_%d: step[%d]\n", n, i);	
		i++;
		kebab_yield(psched);
	}	

	return NULL;
}

int main(int argc, char *argv[])
{
	kebab_sched_st *psched = kebab_init();
	int pid = 0, i = 0, run = 0;
	int total = atoi(argv[1]);

	srand(time(NULL));
	for (i = 0; i < total; i++) {
		int r_num = rand()%10;
		pid = kebab_new(psched, func_a, (void*)r_num);	
	}

	printf("%p\n", &i);
	
	while (1) {
		run = 0;	
		for (i = 0; i < total; i++) {
			if (kebab_status(psched, i) != ROUTINE_DEAD) {
				kebab_resume(psched, i);
				run++;
			}
		}
		if (run == 0) 
			break;	
	}
	
	printf("main thread!\n");
	kebab_destroy(psched);

	return 0;
}

