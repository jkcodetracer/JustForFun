/*
 * @FileName: sock_i.c
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
 * @Date: 2012年05月23日星期三07:22:01
 * 
 */ 

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>

int
open_clientfd(char *hostname, int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;

	if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}

	if((hp = gethostbyname(hostname)) == NULL)
		return -2;

	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;	//不指定协议组 connect不会失败...但是使用的时候，就意外退出了...
	bcopy((char *)hp->h_addr, (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
	serveraddr.sin_port = htons(port);

	if(connect(clientfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
		return -1;
	return clientfd;
}

int
open_listenfd(int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			return -1;
	//地址复用SOL_SOCKET
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
					(const void*)&optval, sizeof(int)) < 0)
		return -1;
	
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons((unsigned short)port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	printf("ip: %s\n", inet_ntoa(serveraddr.sin_addr));

	if(bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
		return -1;
#define LISTENQ		(128)
	if(listen(listenfd, LISTENQ) < 0)
		return -1;
	
	return listenfd;
}


