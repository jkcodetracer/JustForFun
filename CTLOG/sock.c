/**
 * \file sock.c
 * \author  wzj
 * \brief socket interface
 * \version 1.0
 * \note  
 * \date: 2012年08月04日星期六12:41:24
 */ 

#include <fcntl.h>

#include "sock.h"

int un_sock_init(const char *sock_path, struct sockaddr_un *sock_addr)
{
	int sock_fd = 0;
	int ret = 0;

	if(sock_path == NULL || sock_addr == NULL)
	{
		return -1;
	}

	bzero(sock_addr, sizeof(*sock_addr));
	sock_addr->sun_family = AF_UNIX;
	strncpy(sock_addr->sun_path, sock_path, strlen(sock_path));	

	sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		perror("init socket error");
		return -1;
	}
	/* default is NONBLOCK. */	
	/* get the socket flag. */
	int flag = fcntl(sock_fd, F_GETFL, 0);
	if(flag == -1)
	{
		perror("get file flag failed!");	
		return -1;
	}
	/* set the socket flag! */
	ret = fcntl(sock_fd, F_SETFL, flag | O_NONBLOCK);	
	if(ret != 0)
	{
		perror("set O_NONBLOCK failed!");	
		return -1;
	}
	/*
	unsigned long ul = 1;
	// set non block
	ioctl(sock_fd, FIONBIO, &ul);	
	*/

	struct timeval tm = {3, 0};
	setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tm, sizeof(tm));
	setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, &tm, sizeof(tm));

	return sock_fd;
}

int un_sock_close(int fd)
{
	int ret = 0;

	ret = close(fd);

	return ret;
}
