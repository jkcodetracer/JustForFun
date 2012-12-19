/**
 * \file list.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年09月12日星期三23:29:50
 */ 

#include <stdio.h>

#ifndef _LIST_H_
#define _LIST_H_

typedef struct _list_st{
	struct _list_st *prev;	
	struct _list_st *next;
}list_st;

#define GET_ENTRY(p, type, item)	((char*)p - ((size_t)&((type*)0)->item)) 
#endif

typedef struct _test_st{
	int ab;
	int cd;
}test_st;

int main()
{
	test_st test = {1123, 34};	
	int *pint = &(test.cd);

	test_st *ptest = (test_st *)
						GET_ENTRY(pint, test_st, cd);

	printf("%d\n", ptest->ab);

	return 0;
}
