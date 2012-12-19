/**
 * \file shellcode.c
 * \author  wzj
 * \brief shell code~..
 * \version 
 * \note  
 * \date: 2012年08月05日星期日23:29:14
 * 
 */ 
#include <stdio.h>

int main()
{
	char *name[2];

	name[0] = "/bin/sh";
	name[1] = NULL;
	execve(name[0], NULL);

	return 0;
}
