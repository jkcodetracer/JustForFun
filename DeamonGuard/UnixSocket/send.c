#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define TEST_PATH "/home/joker/testdomain.sock"

int main(int argc, char *argv[])
{
	int sockfd = 0;
	struct sockaddr_un addr;
	bzero(&addr, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, TEST_PATH);
	printf("%s\n", TEST_PATH);

	sockfd = socket(AF_UNIX, SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket error.");
		return -1;
	}


	while(1)
	{
		static int counter = 0;
		char send_buf[20] = "";
		counter++;
		sprintf(send_buf, "Counter is %d", counter);
		
		int len = strlen(addr.sun_path) + sizeof(addr.sun_family);
		sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr*)&addr, len);
		printf("Send: %s\n", send_buf);
		sleep(1);
	}

	return 0;
}
