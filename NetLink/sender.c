/*
 * @FileName: sender.c
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
 * @Date: 2012年02月10日星期五23:34:07
 * 
 */ 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>
#include<asm/types.h>
#include<sys/socket.h>
#include<linux/netlink.h>
#include<sys/select.h>

#define MAX_PAYLOAD	1024

struct sockaddr_nl saddr, daddr;
struct msghdr msg;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sd;

int main()
{
	sd = socket(PF_NETLINK, SOCK_RAW, 28);
	if (sd == -1)
	{
		perror("socket error \n");
		exit(1);
	}

	memset(&saddr, 0, sizeof(saddr));
	memset(&daddr, 0, sizeof(daddr));
	saddr.nl_family = AF_NETLINK;
	saddr.nl_pid = getpid();
	saddr.nl_groups = 1;
	bind(sd, (struct sockaddr*)&saddr, sizeof(saddr));
	daddr.nl_family = AF_NETLINK;
	daddr.nl_pid = 0;
	daddr.nl_groups = 1;
	
	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;

	strcpy(NLMSG_DATA(nlh), "crazy summers call kernel!\n");
	iov.iov_base = (void*) nlh;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_name = (void*)&daddr;
	msg.msg_namelen = sizeof(daddr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	printf("Sent message to kernel\n");
	sendmsg(sd, &msg, 0);
	printf("Waiting for message from kernel\n");
	memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
	recvmsg(sd, &msg, 0);
	printf("Received message from kernel that send to it: %s\n", NLMSG_DATA(nlh));
	close(sd);
}


