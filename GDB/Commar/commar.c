/**
 * \file commar.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月08日星期三20:08:11
 * 
 */ 
#include <stdio.h>

int main()
{
	int i = 0;

	i = ({int b = 13;int c = 123; c+b;});

	return 0;
} 

