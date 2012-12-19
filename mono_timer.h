/*
 * @FileName: mono_timer.h
 * @Author: wzj
 * @Brief: 
 * 1. get the ticks to coculate your program costs 
 * 2. compile with the -lrt 
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月26日星期四07:23:07 * */ 
#ifndef __CT_TIMER__

#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

struct timespec begin_timer;
struct timespec end_timer;

#define BEGIN_TIMER	do{		\
		clock_gettime(CLOCK_MONOTONIC, &begin_timer);	\
	}while(0)

#define END_TIMER	do{			\
		clock_gettime(CLOCK_MONOTONIC, &end_timer);		\
	}while(0)	

#define PRINT_COSTS	do{			\
		printf("%s:%d cost: %lu\n", __FUNCTION__, __LINE__, \
			(end_timer.tv_nsec - begin_timer.tv_nsec)/100000);		\
	}while(0)

#endif

