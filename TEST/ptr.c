/**
 * \file ptr.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月11日星期六23:03:15
 * 
 * discript your detail info.
 */ 

#include<stdio.h>

int main()
{
	int a[3] = {1,2,3};
	int (*ptr)[4] = &a;

	for(int i = 0; i < 3; ++i)
	{
		printf("%d\t", (*ptr)[i]);
	}

	return 0;
}
