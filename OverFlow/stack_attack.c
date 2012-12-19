/**
 * \file stack_attack.c
 * \author  wzj
 * \brief  stack attack...
 * \version 
 * \note  
 * \date: 2012年08月05日星期日23:16:55
 * 
 * discript your detail info.
 */ 
#include <stdio.h>

int test()
{
	int a = 0, b=3;

	return a+b;
}

int main()
{
	char name[8];
	printf("Please type your name.\n");
	gets(name);
	printf("hello , %s!", name);
	test();

	return 0;
}
