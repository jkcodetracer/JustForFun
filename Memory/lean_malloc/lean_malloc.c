/**
 * \file lean_malloc.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年08月04日星期日14:01:21
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Jlog.h"

typedef struct _lean_node_st{
	int length;						/* include the head */
	struct _lean_node_st *prev;
	struct _lean_node_st *next;
}lean_node_st;

typedef struct _lean_mng_st{
	int total_length;
	int rest_length;
	char *area;
	char *free_head;
}lean_mng_st;

#define MA8(size) 	(((size+7)>>3)<<3)
#define MIN_SIZE	sizeof(lean_node_st)
#define REAL_SIZE(size)	MA8((size > MIN_SIZE? size: MIN_SIZE) + sizeof(size_t))

lean_mng_st* lean_mng_create(int size)
{
	lean_mng_st *pmng = NULL;
	lean_node_st *pnode = NULL;

	pmng = (lean_mng_st*)malloc(sizeof(lean_mng_st) + size);
	if (pmng == NULL) {
		dblog("malloc manager failed!");
		return NULL;
	}

	pmng->total_length = size;	
	pmng->rest_length = size;
	pmng->area = (char*)(pmng + 1);
	pmng->free_head = pmng->area;
	pnode = (lean_node_st *)pmng->free_head;
	pnode->prev = NULL;
	pnode->next = NULL;
	pnode->length = size;

	return pmng;
}

void lean_mng_destroy(lean_mng_st *pmng)
{
	if (pmng != NULL) {
		free(pmng);	
	}
}

void *lean_malloc(lean_mng_st *pmng, int size)
{
	if (pmng == NULL || size <= 0) {
		dblog("invalid input!");	
		return NULL;
	}	

	int length = REAL_SIZE(size);
	if (length > pmng->rest_length) {
		dblog("no empty memory left!");	
		return NULL;
	}			

	lean_node_st *pnode = NULL;
	pnode = (lean_node_st *) pmng->free_head;
	for (;pnode != NULL; pnode = pnode->next) {
		if (pnode->length > length) {
			break;	
		}	
	}

	if (pnode == NULL) {
		dblog("no suitful area!");	
		return NULL;
	}
	
	if (pnode->length < (length + MIN_SIZE)) {
		if ((size_t)pnode == (size_t)pmng->free_head) {
			pmng->free_head = (char *)pnode->next;	
		}		

		if (pnode->prev != NULL) {
			pnode->prev->next = pnode->next;	
		}

		if (pnode->next != NULL) {
			pnode->next->prev = pnode->prev;	
		}

		length = pnode->length;
	} else {
		lean_node_st *new_node = NULL;	

		new_node = (lean_node_st *) ((size_t)pnode + length);
		new_node->length = pnode->length - length;
		new_node->prev = pnode->prev;
		new_node->next = pnode->next;

		if (pnode->prev != NULL) {
			pnode->prev->next = new_node;		
		}

		if (pnode->next != NULL) {
			pnode->next->prev = new_node;	
		}

		if ((size_t)pmng->free_head == (size_t)pnode) {
			pmng->free_head = (char *)new_node;	
		}
		pnode->length = length;
	}
	pmng->rest_length -= length;

	return (void *)((size_t)pnode + sizeof(size_t));
}

static void lean_do_merge(lean_mng_st *pmng, lean_node_st *pprev, lean_node_st *pnext)
{
	if (pmng == NULL || pprev == NULL || pnext == NULL) {
		dblog("merge prev && next failed!");	
		return ;
	}
	
	pprev->next = pnext->next;
	pprev->length += pnext->length;

	if (pnext->next != NULL) {
		pnext->next->prev = pprev;	
	}

	if ((size_t)pmng->free_head == (size_t)pnext) {
		pmng->free_head = (char *)pprev;	
	}
}

static void lean_merge(lean_mng_st *pmng, lean_node_st *pfree)
{
	if (pmng == NULL || pfree == NULL) {
		dblog("merge failed!");	
		return ;
	}

	lean_node_st *pprev = pfree->prev;
	lean_node_st *pnext = pfree->next;

	if (pnext != NULL &&
		((size_t)pfree + pfree->length) == (size_t)pnext) {
		lean_do_merge(pmng, pfree, pnext);		
		//lean_merge(pmng, pfree);
	}

	if (pprev != NULL && 
		((size_t)pprev + pprev->length) == (size_t)pfree) {
		
		lean_do_merge(pmng, pprev, pfree);
		//lean_merge(pmng, pprev);	
	}
}

void lean_free(lean_mng_st *pmng, void *parea)
{
	if (pmng == NULL || parea == NULL) {
		dblog("Invalid params!");	
		return ;
	}	
	
	lean_node_st *iter = (lean_node_st *)pmng->free_head;
	lean_node_st *free_node = (lean_node_st *) ((size_t)parea - sizeof(size_t));
	free_node->next = NULL;
	free_node->prev = NULL;
	pmng->rest_length += free_node->length;	

	if (iter == NULL) {
		pmng->free_head = (char*)free_node;	
		return ;
	}
	
	printf("free_node:[%p]---length[%d]\n", free_node, free_node->length);
	for(;iter != NULL; iter = iter->next) {
		if (iter > free_node) {
			free_node->next = iter;	
			free_node->prev = iter->prev;

			if (iter->prev != NULL) {
				iter->prev->next = free_node;	
			}
			iter->prev = free_node;

			if (iter == (lean_node_st *)(pmng->free_head)) {
				pmng->free_head = (char* )free_node;	
			}

			break;
		}	

		if (iter->next == NULL) {
			iter->next = free_node;		
			free_node->prev = iter;
			break;
		}
	}
	lean_merge(pmng, free_node);
}

void lean_free_walk(lean_mng_st *pmng)
{
	int i = 0;
	lean_node_st *pnode = NULL;
	pnode = (lean_node_st *)pmng->free_head;
	
	for(; pnode != NULL; pnode = pnode->next) {
		sleep(1);
		printf("free block[%d] address[%p] length[%d]\n", i++, pnode, pnode->length);			
	}
}

int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int total = atoi(argv[1]);
	int pertotal = (total-MIN_SIZE*10)/10;
	int tmp_length = 0;
	lean_mng_st *pmng = lean_mng_create(total);
	char *buff[10] = {NULL};	
	
	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		printf("----%d test! -----pertotal[%d]--\n", i, pertotal);	
		for (j = 0; j < 10; j++) {
			tmp_length = rand()%pertotal;	
			buff[j] = lean_malloc(pmng, tmp_length);
			printf("--malloc[%d]---size[%d]---real[%x]---begin[%p]\n", j, tmp_length, (REAL_SIZE(tmp_length)),buff[j]);
		}

		//lean_free_walk(pmng);
		for (j = 0; j < 10; j++) {
			if (rand()%2 && buff[j] != NULL){
				printf("--free[%d]---begin[%p]\n", j, buff[j]);
				lean_free(pmng, buff[j]);	
				buff[j] = NULL;
			}	
		}

		lean_free_walk(pmng);

		for(j = 0; j < 10; j++) {
			if (buff[j] != NULL) {
				printf("--free[%d]--begin[%p]\n", j, buff[j]);	
				lean_free(pmng, buff[j]);
				buff[j] = NULL;
			}	
		}
		lean_free_walk(pmng);
		printf("----%d test over -------\n", i);	
	}	
	return 0;		
}




