/*
 * @FileName: globalvartest.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月26日星期四23:03:50
 * 
 */ 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int
main()
{
	int fd, num;

	fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("open /dev/globalvar O_RDWR, S_IWUSR S_IRUSR");	
		return -1;
	}

	read(fd, &num, sizeof(num));
	printf("The global var is %d\n", num);
	
	num = 3123;
	write(fd, &num, sizeof(num));
	
	read(fd, &num, sizeof(num));
	printf("The gloval var is %d\n", num);

	close(fd);

	return 0;
}
