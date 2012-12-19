/**
 * \file logd.c
 * \author  wzj
 * \brief log listener
 * \version 1.0
 * \note  
 * \date: 2012年08月04日星期六13:06:42
 * 
 */ 
#include <sys/types.h>
#include <sys/times.h>
#include <sys/select.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "logs.h"
#include "sock.h"
#include "logd.h"

//volatile sig_atomic_t g_run = 0;
static int g_run = 0;

/**
 * \brief show frame content
 * \param 
 */
void print_frame(char *rcv_buf)
{
	log_frame_st *pframe = (log_frame_st*) rcv_buf;
	printf("log_type: %d\n", pframe->log_type);
	printf("pid: %d\n", pframe->pid);
	printf("log_buffer: %s\n", pframe->log_buffer);
}

/**
 * \brief read the package frame
 * \param srv_fd 
 * \param rcv_buf
 * \param buf_len
 */
static int read_frame(int srv_fd, char *rcv_buf, int buf_len)
{
	int ret = 0;	

	ret = read(srv_fd, rcv_buf, buf_len);
	if(ret == -1 )
	{
		LOGALARM("read log failed ...");	
		return -1;
	}

	return ret;
}


/**
 * \brief receiv the logs
 * \param srv_fd the listener socket
 */
int log_listener(int srv_fd)
{
	fd_set fake_set;
	int max_sock_fd, ret = 0;
	struct timeval timeout_tv;

	max_sock_fd = srv_fd;
	
	while(g_run)	
	{
		char rcv_buf[sizeof(log_frame_st)] = {'\0'};
		FD_ZERO(&fake_set);	
		FD_SET(srv_fd, &fake_set);

		timeout_tv.tv_sec = 1;
		timeout_tv.tv_usec = 0;

		ret = select(max_sock_fd + 1, &fake_set, NULL, NULL, &timeout_tv);
		if(ret < 0)
		{
			if(errno == EAGAIN || errno == EINTR)
			{
				continue;
			}
			LOGERROR("select run error!");
			g_run = 0;
			break;
		} else if(ret == 0)
		{
			LOGREAL("timeout!");
			/* process the data */
			continue;
		}

		if(FD_ISSET(srv_fd, &fake_set))
		{
			/* ignore the read failed */
			ret = read_frame(srv_fd, rcv_buf, sizeof(rcv_buf));	
			if(ret > 0)
			{
				print_frame(rcv_buf);
			}
			LOGALARM("%d:%s:%d", ret, rcv_buf, sizeof(rcv_buf));
		}
		/* process the data */

	}

	return 0;
}

/**
 * \brief init the unix domain socket
 * \param sock_addr 
 */
int sock_init(struct sockaddr_un *sock_addr, socklen_t *sock_len)
{
	ASSERT(sock_addr != NULL && sock_len != NULL, -1);
	int fd = -1;

	unlink(CT_LOGD_UN_PATH);	
	fd = un_sock_init(CT_LOGD_UN_PATH, sock_addr);
	if(fd == -1)
	{
		LOGALARM("init socket failed");
		return -1;
	}

	int on = 1;
	int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(ret < 0)	
	{
		perror("set soket opt error");
		return -1;
	}

	*sock_len = strlen(sock_addr->sun_path) + sizeof(sock_addr->sun_family);
	ret = bind(fd, (struct sockaddr *)sock_addr, *sock_len);
	if(ret < 0)
	{
		perror("set sock opt error");
		return -1;
	}

	return fd;
}

int main()
{
	int fd = -1;
	struct sockaddr_un sock_addr;
	socklen_t 	sock_len;

	fd = sock_init(&sock_addr, &sock_len);
	if(fd < 0)
	{
		LOGERROR("init logd un socket failed!");	
		return -1;
	}

	g_run = 1;
/*
	while(g_run)
	{
		sleep(2);
		char rcv_buf[200] = "";
		printf("rcv: %s\n", rcv_buf);
		ret = read(fd, rcv_buf, sizeof(rcv_buf) - 1);
		printf("rcv: num:%d %s\n", ret, rcv_buf);
	}
*/
	/* main processor */
	log_listener(fd);	

	un_sock_close(fd);
	return 0;
}

