/**
 * \file vartest.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月06日星期一22:58:04
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <unistd.h>

int main()
{
	FILE *fp = fopen("/dev/globalvar", "r");

	if(fp == NULL)
	{
		printf("open failed...\n");
		return -1;
	}

	while(1)
	{
		int val = 0;
		read(fileno(fp), &val, sizeof(val));
		printf("%d\n", val);
		sleep(3);
	}

	fclose(fp);
	return 0;
}
