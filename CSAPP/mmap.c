/*
 * @FileName: mmap.c
 * @Author: wzj
 * @Brief: 
 * 1.使用mmap生成一个新的页面，用于输出映射的文件。 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月13日星期日12:10:41
 * 
 */ 
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int 
mymmap(int fd, int size)
{
	char* brp = NULL;
	//映射磁盘上的文件
	brp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	//输出到stdout
	write(1, brp, size);
}

int 
main(int argc, char* argv[])
{
	int fd = -1;
	int file_sz = 0;
	struct stat buf;

	if(argc != 2)
	{
		write(1, "xxx: argc\n", sizeof("xxx:argc\n"));
		return -1;
	}

	stat(argv[1], &buf);	
	//打开文件
	fd = open(argv[1], O_RDONLY);
	mymmap(fd, buf.st_size);

	return 0;


}
