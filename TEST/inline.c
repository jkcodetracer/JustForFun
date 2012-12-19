/*
 * @FileName: inline.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月14日星期六21:45:19
 * 
 */ 
#include <stdio.h>
#include "inline.h"
#if 0
inline int
plus(const int a , const int b)
{
	int i = 0;

	i = a + b;

	return i;
}
#endif

int 
main()
{
	int ret = 0;

	ret = plus(2,4);

	printf("result = %d\n", ret);

	return 0;
}
