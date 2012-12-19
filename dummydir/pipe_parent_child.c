/**
 * \file pipe_parent_child.c
 * \author  wzj
 * \brief 
 	父子通信
 * \version 
 * \note  
 * \date: 2012年10月05日星期五07:12:08
 */ 

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

static int fds1[2], fds2[2];

void tell_wait()
{
	if(pipe(fds1) < 0 || pipe(fds2) < 0)
	{
		printf("init pipe failed! errno:[%d]\n", errno);
		return ;
	}
}

void tell_parent(pid_t pid)
{
	if(write(fds2[1], pid, sizeof(pid)) != sizeof(pid))	
	{	/* maybe pipe broken */
		printf("tell parent failed!\n");
		return ;
	}
}

pid_t wait_parent()
{
	int pid;

	if(read(fds1[0], pid, sizeof(pid)) != sizeof(pid))
	{
		printf("wait parent failed!\n");
		return;
	}
	
	return pid;
}

void tell_child(pid_t pid)
{
	if(write(fds1[1], pid, sizeof(pid)) != sizeof(pid))
	{
		printf("tell child failed\n");
		return ;
	}
}

pid_t wait_child()
{
	int pid;

	if(read(fds2[0], pid, sizeof(pid)) != sizeof(pid))
	{
		printf("wait child failed!\n");
		return ;
	}

	return pid;
}


