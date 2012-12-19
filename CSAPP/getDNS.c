/*
 * @FileName: getDNS.c
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
 * @Date: 2012年05月22日星期二06:38:20
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main(int argc, char **argv)
{
	char **pp;
	struct in_addr addr;
	struct hostent *hostp;

	if(argc != 2)
	{
		fprintf(stderr, "...");
		return -1;
	}

	if(inet_aton(argv[1], &addr) != 0)
		hostp = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
	else
		hostp = gethostbyname(argv[1]);
	
	printf("official hostname: %s\n", hostp->h_name);

	for(pp = hostp->h_aliases; *pp != NULL; pp++)
		printf("alias: %s\n", *pp);

	for(pp = hostp->h_addr_list; *pp != NULL; pp++)
	{
		addr.s_addr = *((unsigned int *)*pp);
		printf("address:%s\n", inet_ntoa(addr));
	}

	return 0;
}
