/**
 * @file  xheap.c
 * @author  wzj
 * @brief 
 * @version 
 * @note  
 * @date: 2012年08月01日星期三22:27:52
 * 
 * discript your detail info.
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xheap.h"
#include "../Jlog.h"

#define DEFAULT_SIZE	(32)
#define SAFE_FREE(p) if(p)	{	\
			free(p), p = NULL;	\
		}

void* zeromalloc(unsigned int size)
{
	void *buf = NULL;	
	buf = malloc(size);
	if(buf)
		memset(buf, 0, size);

	return buf;
}

int default_cmp_func(void *a, void *b)
{
	return (a > b);
}
/**
 * take care the cmpfunc
 */
xheap_st *heap_create(cmp_func_t cmpfunc, unsigned int heap_size) 
{
	xheap_st *pheap = NULL;
	
	pheap = (xheap_st*)zeromalloc(sizeof(xheap_st));
	if(pheap == NULL)	
		return pheap;
	/* when we use it, we alloc it. */
	pheap->base = NULL;
	pheap->nbase = heap_size ? heap_size:DEFAULT_SIZE;
	pheap->heap_size = 0;

	if(cmpfunc != NULL)
	{
		pheap->cmp = cmpfunc; 
	} else {
		pheap->cmp = default_cmp_func;
	}
	
	return pheap;
}

/**
 * destroy the heap 
 */
void heap_destroy(xheap_st *pheap)
{
	if(pheap == NULL)
		return ;

	SAFE_FREE(pheap->base);	
	SAFE_FREE(pheap);
}

#define swap(a, b) do{	\
		void* tmp = a;	\
			a = b;		\
			b = tmp;	\
		}while(0)

/**
 * push in an value
 */
int heap_push(xheap_st *pheap, void *data)
{
	if(pheap == NULL || data == NULL)	
		return -1;
	
	if(pheap->base == NULL)
	{
		pheap->base = (void **)zeromalloc(sizeof(void*) * pheap->nbase);
		if(pheap->base == NULL)
			return -1;
	}

	if(pheap->heap_size >= pheap->nbase)
	{
		pheap->base = (void**)realloc(pheap->base, pheap->nbase << 1);
		if(pheap->base == NULL)
			return -1;
		pheap->nbase = pheap->nbase << 1;
	}

	unsigned int index, parent;	
	index = pheap->heap_size++;
	pheap->base[index] = data;
	
	while(index)
	{
		parent = (index - 1) >> 1;	

		if(pheap->cmp(pheap->base[index], pheap->base[parent]))
			swap(pheap->base[index], pheap->base[parent]);
		
		index = parent;
	}

	return 0;
}

/**
 * pop the root; 
 */
int heap_pop(xheap_st *pheap, void **data)
{
	if(pheap == NULL)
		return -1;
	
	if(pheap->base == NULL)
		return -1;
	
	if(data != NULL)
		*data = pheap->base[0];
	
	unsigned int index = --pheap->heap_size;
	pheap->base[0] = pheap->base[index];

	index = 0;

	while(index < pheap->heap_size)
	{
		unsigned int lchild = (index << 1) + 1;	
		unsigned int rchild = (index << 1) + 2;
		unsigned int cmp_index = 0;

		if(pheap->base[lchild] == NULL)
			break;

		if(pheap->base[rchild] == NULL)
		{
			cmp_index = lchild;	
		} else {
			cmp_index = (pheap->cmp(pheap->base[lchild], pheap->base[rchild]))?rchild:lchild;	
		}

		if(!pheap->cmp(pheap->base[cmp_index], pheap->base[index]))
			break;

		swap(pheap->base[cmp_index], pheap->base[index]);
		index = cmp_index;
	}

	return 0;
}

int main()
{
	xheap_st *pheap;
	int tmp;
	pheap = heap_create(NULL, 34);
	
	printf("1");
	heap_push(pheap,(void*)32);
	heap_push(pheap,(void*)24);
	heap_push(pheap,(void*)53);
	heap_push(pheap,(void*)12);

	heap_pop(pheap, (void**)&tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	printf("%d\n", tmp);

	
	heap_push(pheap,(void*)123);
	heap_push(pheap,(void*)1244);
	heap_push(pheap,(void*)5);
	heap_push(pheap,(void*)12);
	heap_push(pheap,(void*)32);
	heap_push(pheap,(void*)24);
	heap_push(pheap,(void*)53);
	heap_push(pheap,(void*)12);
	
	heap_pop(pheap, (void**)&tmp);
	DUMPLOG("./test.txt", "%d\n", tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	DUMPLOG("./test.txt", "%d\n", tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	DUMPLOG("./test.txt", "%d\n", tmp);
	printf("%d\n", tmp);
	heap_pop(pheap, (void**)&tmp);
	DUMPLOG("./test.txt", "%d\n", tmp);
	printf("%d\n", tmp);
	return 0;
}

