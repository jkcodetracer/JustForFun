/**
 * \file ctarray.c
 * \author  wzj
 * \brief 
 	simple array...
 * \version 
 * \note  
 * \date: 2012年11月10日星期六06:58:40
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <Jlog.h>

#include "ctarray.h"

ct_array_st *ct_array_creat(unsigned int size, 
							unsigned int nalloc,
							void *allocator)
{
	ct_array_st *parray = NULL;	

	if(allocator != NULL)
	{
		/* TODO with the allocator*/
		return NULL;
	}

	parray = (ct_array_st *)malloc(sizeof(*parray));
	if(parray == NULL)
	{
		WRITELOG("malloc ct_array_st failed!");
		goto FAILED_EXIT;
	}
	memset(parray, 0, sizeof(*parray));
	
	parray->nelts = 0;
	parray->size = size;
	parray->nalloc = nalloc;
	parray->allocator = NULL;
	parray->elts = malloc(size * nalloc); 
	if(parray->elts == NULL)
	{
		WRITELOG("malloc elts failed!");
		goto FAILED_EXIT;
	}
	
	return parray;
	
FAILED_EXIT:

	SAFE_FREE(parray->elts);
	SAFE_FREE(parray);
	
	return NULL;
}

void ct_array_destroy(ct_array_st *parray)
{
	if(parray == NULL)
		return;

	if(parray->allocator != NULL)
	{
		/* TODO */
	}

	SAFE_FREE(parray->elts);	
	SAFE_FREE(parray);
}

void *ct_array_push(ct_array_st *parray)
{
	ASSERT(parray != NULL, NULL);
	void *palloc = NULL;

	if(parray->nelts == parray->nalloc)
	{
		/* TODO use the allocator */	
		void *fake_elts = NULL;				
		int  size = (parray->nalloc << 1)* parray->size;
		fake_elts = realloc(parray->elts, size);
		if(fake_elts == NULL)
		{
			WRITELOG("realloc failed!");
			return NULL;
		}

		parray->nalloc <<= 1;
		parray->elts = fake_elts;
		WRITELOG("current nalloc:[%d]", parray->nalloc);
	}

	palloc = parray->elts + parray->nelts * parray->size;
	parray->nelts++;

	return palloc;
}

void *ct_array_push_n(ct_array_st *parray, unsigned int len)
{
	ASSERT(parray != NULL, NULL);	
	void *palloc = NULL;

	if(parray->nelts + len >= parray->nalloc)
	{
		int size = (parray->nelts + len) << 1;	
		void *fake_elts = realloc(parray->elts, size);
		if(fake_elts == NULL)
		{
			WRITELOG("realloc elts failed!");
			return NULL;
		}

		parray->elts = fake_elts;
		parray->nalloc = size;

		WRITELOG("current nalloc:[%d]", parray->nalloc);
	}

	palloc = parray->elts + parray->nelts * parray->size;
	parray->nelts+= len;

	return palloc;
}


int main(int argc, char *argv[])
{
	int i = 0; 
	ct_array_st *newarray = NULL;
	char *str = NULL;

	newarray = ct_array_creat(sizeof(int), 5, NULL);
	if(newarray == NULL)
	{
		WRITELOG("new array alloc failed!");
		return -1;
	}

	for(i = 0; i < 20; i++)
	{
		str = (char*)ct_array_push(newarray);
		WRITELOG("current pos:[%x]", (unsigned int)str);
	}

	ct_array_destroy(newarray);

	newarray = ct_array_creat(sizeof(int), 5, NULL);
	if(newarray == NULL)
	{
		WRITELOG("new array alloc failed!");
		return -1;
	}

	for(i = 0; i < 20; i++)
	{
		str = (char*) ct_array_push_n(newarray, i * 8);
		WRITELOG("current pos:[%x]", (unsigned int)str);
	}

	ct_array_destroy(newarray);

	return 0;
}




