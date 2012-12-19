/**
 * \file showplug.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月26日星期日20:29:17
 */ 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = 0;
	int ret = 0;
	char buf[12];
	
	fd = open("/dev/plugbase", O_RDWR);
	if(fd < 0)
	{
		printf("open dev failed!\n");
		return 0;
	}
	
	read(fd, buf, 12);	

	return 0;
}
