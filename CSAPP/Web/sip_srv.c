/*
 * @FileName: sip_srv.c
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
 * @Date: 2012年05月27日星期日11:24:35
 * 
 */ 
#include "sock_i.h"
#include "rio.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void echo(int connfd);

int
main(int argc, char **argv)
{
	int listenfd, connfd, port, clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;

	if(argc != 2){
		printf("...");
		return -1;
	}

	port = atoi(argv[1]);

	listenfd = open_listenfd(port);
	while(1)
	{
		printf("wait:\n");
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (struct sockaddr*)&clientaddr,&clientlen);
		
		hp = gethostbyaddr((const char*)&clientaddr.sin_addr.s_addr,
					sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		
		echo (connfd);
		close(connfd);
	}
	return 0;	
}

void 
echo(int connfd)
{
	size_t n;
	char buf[1024];
	rio_t rio;

	rio_initb(&rio, connfd);
	while((n = rio_readlineb(&rio, buf, 1024)) != 0) {
		printf("...server: %d\n", n);
		rio_writen(connfd, buf, n);
	}
}
