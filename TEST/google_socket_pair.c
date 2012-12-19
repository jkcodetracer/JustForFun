/*
 * @FileName: google_socket_pair.c
 * @Author: wzj
 * @Brief: 
 * 1.A.B.C.D四个进程，每个进程分别只写1.2.3.4 
 * 2.对应ABCD四个文件 得到如下的输入 
 * 		A.1 2 3 4 1 2 3 4
 * 		B.2 3 4 1 2 3 4 1  
 *		C.3 4 1 2 3 4 1 2
 * 		D.4 1 2 3 4 1 2 3 
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年04月15日星期日18:14:16
 * 
 */ 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

typedef struct file_node{
	int r_pipe;
	int w_pipe;
	int fd;
}file_node;

char *file[] = {"./a", "./b","./c","./d"};

file_node node_list[4];

void *thread_func(void *arg);

int main()
{
	int *num, i;
	int sockpair[2];
	pthread_t thd_id;

	memset(node_list, 0, sizeof(node_list));

	for(i = 0; i<4; i++)
	{
		if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockpair))
		{
			printf("socketpair error !\n");
			return -1;
		}
		node_list[i].w_pipe = sockpair[0];
		
		if(i != 3)
			node_list[i+1].r_pipe = sockpair[1];
		else
			node_list[0].r_pipe = sockpair[1];

		node_list[i].fd = open(file[i], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
		if(node_list[i].fd < 0)
		{
			printf("open fd error, exit!\n");
			return 0;
		}
	}

	for(i = 0; i < 4; i++)
	{
		num = (int*) malloc(sizeof(int));
		*num = i;
		pthread_create(&thd_id, NULL, thread_func, num);
	}

	pause();
}

void* thread_func(void* arg)
{
	pthread_t 	pid;
	char		buf[100] = {'\0'};
	int 	w_fd, num,i;
	int buf_len = 0;

	num  = *(int*)arg;
	free(arg);
	printf("%d\n", num);

	pid = pthread_self();
	pthread_detach(pid);
	
	sprintf(buf, "%d", num+1);
	buf_len = strlen(buf);
	w_fd = node_list[num].fd;

	while(i < 10)
	{
		if(write(w_fd, (void*)buf, buf_len) != buf_len)
		{
			break;
		}

		if(write(node_list[num].w_pipe, (void*)&w_fd,sizeof(int)) != sizeof(int))
		{
			break;		
		}

		if(read(node_list[num].r_pipe, &w_fd, sizeof(int)) != sizeof(int))
		{
			break;
		}
		i++;
	}

	pthread_exit(0);
}
