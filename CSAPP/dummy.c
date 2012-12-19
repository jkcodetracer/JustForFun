#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int 
main(int argc, char **argv)
{
	struct hostent *s_host;
	struct in_addr addr_tmp;

	if(argc < 1)
	{
		return -1;
	}

	if(inet_aton(argv[1], &addr_tmp))
	{
		s_host = gethostbyaddr(&addr_tmp, sizeof(addr_tmp),AF_INET);		
	} else {
		s_host = gethostbyname(argv[1]); 
	}

	if(s_host == NULL)
	{
		return -1;
	}
	
	printf("official name: %s\n", s_host->h_name);
	
	char** hp = NULL;
	printf("h_aliases:\n");
	for(hp = s_host->h_aliases; *hp != NULL; hp++)
	{
		printf("%s\n", *hp);
	}

	printf("addr_list:\n");
	for(hp = s_host->h_addr_list; *hp != NULL; hp++)
	{
		printf("%s\n", *hp);
		addr_tmp.s_addr = *((unsigned int*) *hp);
		printf("address: %s\n", inet_ntoa(addr_tmp));
	}

	return 0;

}
