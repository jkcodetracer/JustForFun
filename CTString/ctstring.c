/**
 * \file ctstring.c
 * \author  wzj
 * \brief 
 * \version 
 	string opr
 * \note  
 * \date: 2012年11月11日星期日07:48:17
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ctstring.h"

void ct_strlow(char *dst, const char *src, size_t n)
{
	while(n){
//		*dst = ct_tolower(*src);	
		dst++;
		src++;
		n--;
	}
}


char *ct_vslprintf(char *buf, const char *fmt, ...)
{
	va_list args;
	char zero;

	va_start(args, fmt);
	
	while(*fmt)
	{
		if(*fmt == '%')	
		{
			/* control part */
			/* the real format, get the var */

		}else {
			/* do the copy */	
		}
	}

	va_end(args);

	return NULL;
}

char *ct_hex_dump(char *dst, const char *src, size_t len)
{
	static char hex[] = "0123456789ABCDEF";	

	while(len)
	{
		*dst++ = hex[*src >> 4];
		*dst++ = hex[*src++ & 0xf];
		len--;
	}

	return dst;
}

int main(int argc, char *argv[]) 
{
	int mark = 0;
	int i = 0;
	char dst[128] = {'\0'};
	char *result = NULL;
	char *src = "mbcdefghijklmnopqrstuvwxyz";

	result = ct_hex_dump(dst, src, 15);
	result = dst;

	for(i = 0; i < 15; i++)
	{
		printf("%c", result[i]);
	}
	printf("[%s]\n", result);

	return 0;
}



