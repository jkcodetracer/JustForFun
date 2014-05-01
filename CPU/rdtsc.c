/**
 * \file rdtsc.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年07月18日星期四07:33:17
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <stdlib.h>


#define _mu64 unsigned long long

_mu64 myrdtsc()
{
	unsigned int lo, hi;

	__asm__ __volatile__(
	"rdtsc"
	:"=a"(lo), "=d"(hi)
	);

	return (_mu64)hi << 32 | lo;
}

int main()
{
	int i = 0, j = 0;
	_mu64 begin, end;
	
	begin = myrdtsc();
	for(i = 0 ; i<10; i++) {
		j += i;
	}
	end = myrdtsc();
	printf("test\n");

	printf("%lld\n", end - begin);

	return 0;
}

