/*
 * @FileName: jUnixSock.c
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
 * @Date: 2012年03月25日星期日22:53:51
 * 
 */ 

#include "jUnixSock.h"
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

int create_unix_sock(const char* sock_path)
{
	int sock_fd = 0;
	int on = 0;
	int ret = 0;
	struct sockaddr_un sock_addr;
	socklen_t len = 0;

	if(sock_path == NULL)
	{
		return -1;	
	}
	unlink(sock_path);	
	bzero(&sock_addr, sizeof(sock_addr));
	strncpy(sock_addr.sun_path, sock_path, sizeof(addr.sun_path) - 1);
	len = strlen(addr.sun_path + sizeof(addr.sun_family));	

	sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock_fd < 0)
	{
		return -1;
	}

	on = 1;
	ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(ret < 0)
	{
		return -1;
	}

/*	if(bind(sock_fd, (struct sockaddr *)&addr, len) < 0)
	{
		return -1;
	}
*/
	return sock_fd;
}

int close_unix_sock(int sock_fd)
{
	if(sock_fd > 0)
	{
		close(sock_fd);
	}
}
