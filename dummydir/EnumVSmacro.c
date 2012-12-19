/*
 * @FileName: EnumVSmacro
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
 * @Date: 2012年04月25日星期三21:09:07
 * 
 */ 
#include<stdio.h>

enum {
	FIRST = 1,
	SECOND = 2,
	THIRD = 3
};

#define THIRD (SECOND)

int 
main()
{
	int i = 0;
	printf("THIRD:(r)%d, THIRD:(macro) %d\n", THIRD, THIRD);

	return 0;
}
