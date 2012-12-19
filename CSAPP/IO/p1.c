/*
 * @FileName: p1.c
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
 * @Date: 2012年05月20日星期日22:22:03
 * 
 */ 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int 
main()
{
/*
	FILE *fp = fopen("test.txt", "w");
	if(!fp)
	{
		return -1;
	}
	*/
	int fd = open("test.txt", O_RDWR);
	if(fd == -1)
	{
		printf("...");
		return -1;
	}
	printf("%d\n", fd);

	int ret=lockf(fd, F_LOCK, 0);
	if(ret)
	{
		printf("lock  failed:%s\n", strerror(errno));
	}else {
		printf("lock suceess\n");
	}
	while(1)
	{
		sleep(5);
	//	printf("%p\n", *fp);
	}

	return 0;
}
