/*
 * @FileName: fd.c
 * @Author: wzj
 * @Brief: 
 *     ssize_t === int
 *	   size_t === unsigned int 
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月20日星期日21:04:14
 * 
 */ 
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int 
main()
{
	int fd1, fd2;

	fd1 = open("foo.txt", O_RDONLY, 0);
	close(fd1);

	fd2 = open("baz.txt", O_RDONLY, 0);
	printf("fd2 = %d\n", fd2);

	char c;

	while(read(1, &c, 1) != 0)
	{
		write(2, &c, 1);
	}

	return 0;
}
