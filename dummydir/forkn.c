/**
 * \file forkn.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年10月07日星期日08:12:33
 */ 
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	for(int i = 0; i < 2; ++i)
	{
		int j = fork();
		fflush(stdout);
		printf("- [%4d] [%4d]   ", i, j);
	}
}
