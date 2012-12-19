#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define TEST_SOCK "/home/joker/testdomain.sock"

int main(int argc, char *argv[])
{
	int sockfd = 0;
	struct sockaddr_un addr;
	int on = 1;
	unlink(TEST_SOCK);

	bzero(&addr, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,  TEST_SOCK, sizeof(addr.sun_path) - 1);
	socklen_t len = strlen(addr.sun_path) + sizeof(addr.sun_family);

	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("socket error");
		return -1;
	}

	on = 1;
	int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(ret < 0)
	{
		perror("set sock opt error");
		return -1;
	}

	if(bind(sockfd, (struct sockaddr *)&addr, len) < 0)
	{
		perror("bind error"); 
		close(sockfd);
		return -1;
	}
	while(1)
	{
		perror("...");
		printf("begin..");
		sleep(5);
		char recv_buf[20] = "";
		//recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &len);
		read(sockfd, recv_buf, sizeof(recv_buf));
		printf("Recv: %s\n", recv_buf);
	}
	return 0;
}
