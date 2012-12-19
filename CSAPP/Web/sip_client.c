/*
 * @FileName: sip_client.c
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
 * @Date: 2012年05月27日星期日09:48:12
 * 
 */ 
#include "sock_i.h"
#include "rio.h"
#include <stdio.h>
#include <string.h>

int
main(int argc, char **argv)
{
	int srv_fd = -1;
	int clt_fd = -1;
	int port = 0;
	char *host,buf[1024];
	rio_t rio;

	if(argc != 3)
	{
		return -1;
	}

	host = argv[1];
	port = atoi(argv[2]);

	clt_fd = open_clientfd(host, port);

	rio_initb(&rio, clt_fd);
	printf("%d\n", clt_fd);

	//while((fgets(buf, sizeof(buf), stdin) != NULL) && (ferror(stdin) == 0))
	while(1)
	{
		if((fgets(buf, sizeof(buf), stdin) == NULL) &&
			ferror(stdin))
		{
			printf("why\n");
			break;
		}
		printf("clinet : %s\n",buf);
		rio_writen(clt_fd, buf, strlen(buf));
		rio_readlineb(&rio, buf, sizeof(buf));

		fputs(buf, stdout);
	}

	return 0;
}
