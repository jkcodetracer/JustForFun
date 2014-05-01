/**
 * \file multythread.c
 * \author  wzj
 * \brief 
 *	 for the spinlock test.
 * \version 
 * \note  
 * \date: 2013年07月22日星期一23:52:25
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include <time.h>
#include <sched.h>

sem_t sem_a;
sem_t sem_b;
sem_t sem_end;

int x = 0;
int y = 0;
int i = 0;
int j = 0;

void *thread_func_a(void *param)
{
	struct timespec sleep_tm = {0, 500};
	
	pthread_detach(pthread_self());
	while(1) {
		sem_wait(&sem_a);
		while(rand()%8){
			//nanosleep(&sleep_tm, NULL);	
		}

		x = 1;
		asm volatile("":::"memory");		
		i = y;
		//printf("TA:%d\n", k);

		sem_post(&sem_end);
		//nanosleep(&sleep_tm, NULL);	
	}

	return NULL;
}

void *thread_func_b(void *param)
{
	struct timespec sleep_tm = {0, 500};
	
	pthread_detach(pthread_self());
	while(1) {
		sem_wait(&sem_b);
		while(rand()%6){
			//nanosleep(&sleep_tm, NULL);	
		}
		y = 1;
		asm volatile("" :::"memory");
		//printf("TB:%d\n", k);
		j = x;
	
		sem_post(&sem_end);
		//nanosleep(&sleep_tm, NULL);	
	}

	return NULL;
}


int main(int argc, char *argv[])
{
	int t = 0;
	pthread_t p_a, p_b;

	sem_init(&sem_a, 0, 0);
	sem_init(&sem_b, 0, 0);
	sem_init(&sem_end, 0, 0);

	srand(time(NULL));
	pthread_create(&p_a, NULL, thread_func_a, NULL);
	pthread_create(&p_b, NULL, thread_func_b, NULL);


	while (1) {
		i = 0;
		j = 0;

		t++;
		sem_post(&sem_a);	
		sem_post(&sem_b);

		sem_wait(&sem_end);
		sem_wait(&sem_end);

		if(i == 0 && j == 0) {
			printf("----%d-------\n", t);	
		}
		//printf("delay:\n");	

	}

	return 1;
}

