/**
 * @file  comma_local.c
 * @author  wzj
 * @brief 
 * @version 
 * @note  
 * @date: 2012年08月02日星期四22:59:48
 * 
 * discript your detail info.
 */ 

#include <stdio.h>

int main()
{
	int i = 0;
	while(i < 5)
	{
		int j = 10;
		j++, i++;
		printf("%d", j);
	}

	while(i < 10)
	{
		int j = 0; 
		j++;
		printf("%d", j);
		i++;
	}

	return 0;
}

