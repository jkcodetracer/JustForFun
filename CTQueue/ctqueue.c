/**
 * \file ctqueue.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年11月14日星期三07:20:16
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <Jlog.h>
#include "ctqueue.h"

typedef struct _int_array_st{
	int content;
	ct_queue_st	link;
	int another;
}int_array_st;

int main(int argc, char *argv[])
{
	int i = 0;	
	ct_queue_st  *processor = NULL;
	int_array_st *item = NULL;
	int_array_st head = {'0'};
	int_array_st base = {'0'};
	int_array_st conb = {'0'};

	ct_queue_init(&(head.link));
	ct_queue_init(&(base.link));
	ct_queue_init(&(conb.link));

	for(i = 0; i < 10; i++)
	{
		item = (int_array_st*)malloc(sizeof(*item));
		
		item->content = i;
		item->another = i + 255;
		dblog("insert array:[%d][%d]", 
						item->content, item->another);
		ct_queue_insert_tail(&(head.link), &(item->link));
	}

	processor= head.link.next;
	for(i = 0; i < 10; i++)
	{
		item = ct_queue_data(processor, int_array_st, link);
		dblog("show array:[%d][%d]", 
						item->content, item->another);
		processor = ct_queue_next(processor);
		dblog("[%x]", (unsigned int)processor);
	}

	for(i = 0; i < 10; i++)
	{
		item = (int_array_st*)malloc(sizeof(*item));
		if(item == NULL)
			return 0;
		
		item->content = i * 2;
		item->another = i + 255;
		dblog("insert array:[%d][%d]", 
						item->content, item->another);
		ct_queue_insert_tail(&(base.link), &(item->link));
	}	

	ct_queue_split1(&(base.link), &(head.link), &(conb.link));

	processor = ct_queue_head(&(conb.link));
	dblog("%x\n", (unsigned int)processor);
	for(i = 0; i < 24; i++)
	{
		item = ct_queue_data(processor, int_array_st, link);
		dblog("show array:[%d][%d]", 
						item->content, item->another);
		processor = ct_queue_next(processor);
		dblog("[%x]", (unsigned int)processor);
	}

	return 0;
}


