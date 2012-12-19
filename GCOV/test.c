/**
 * \file test.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date  2012年09月15日星期六23:19:31
 */ 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i = 0;

	printf("Begin Test...\n");
	if(1 == argc)
	{
		printf("argc == 1\n");
	} else {
		printf("argc != 1\n");
		for(i = 0; i < argc; i++)
			printf("%d to ft %d\n", i+1, argc);
	}
	while(1)
	{
		if(i == 10)
			i = 0;
		static int sum = 0;

		if(i%2 == 0)
			sum += i;

		sleep(1);
	}


	printf("End test !\n");
}
