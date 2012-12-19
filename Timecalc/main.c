/**
 * \file main.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年12月03日星期一00:01:38
 * 
 * discript your detail info.
 */ 
#include "mono_timer.h"
#include <stdio.h>
#include <stdlib.h>

struct node_t{
	int a;
	struct node_t *next;
};

int main()
{
	BEGIN_TIMER;
	struct node_t *p;
	int i = 0;
	int size = sizeof(struct node_t);
	
	//while(i < 2000000)
	{
		p = (struct node_t*) malloc(size * 2000000);	
		p->a = 1;
	//	i++;
	}
	while(i < 2000000)
	{
		p[i].a = 1;
		i++;
	}

	END_TIMER;
	PRINT_COSTS;

	while(1)
	{
		sleep(1);
	}

	return 0;
}

