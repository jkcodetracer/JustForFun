/**
 * \file ftp_client.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月29日星期三20:40:36
 */ 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "Jlog.h"

#define CONTROL_PORT 	(21)

int tcp_send(int sock_fd, char *buf, ssize_t len)
{
	int snd_num = 0;
	int ret = 0;

	while(snd_num < len)
	{
		ret = write(sock_fd, buf + snd_num, len - snd_num);	
		if(ret < 0)
		{
			if(errno == EAGAIN ||
			   errno == EINTR)	
			   continue;
			return -1;
		}

		snd_num += ret;
	}

	return snd_num;
}

int ftp_send_cmd(int ctl_fd, const char *format, ...)
{
	char cmd_buf[512] = {'0'};
	int send_len = 0;
	int ret = 0;
	va_list ap;	
	
	va_start(ap, format);
	send_len = vsnprintf(cmd_buf, sizeof(cmd_buf), format, ap);
	va_end(ap);

	if(send_len < -1 || send_len > sizeof(cmd_buf))
	{
		WRITELOG("too long to fullfill the send buffer!");
		return -1;
	}
	WRITELOG("begin send!");
	ret = tcp_send(ctl_fd, cmd_buf, send_len);	
	if(ret != send_len)
	{
		WRITELOG("send error.[%d][%s]", errno, strerror(errno));	
		return -1;
	}

	return 0;
}
int tcp_recv(int sock_fd, char *buf, ssize_t buf_len)
{
	int ret = 0;

		ret = read(sock_fd, buf, buf_len);
	/*	if(ret < 0)
		{
			if(errno == EAGAIN || errno == EINTR)
				continue;
			return -1;
		}
		break;
		*/
		
	buf[ret] = '\0';
	
	return ret;
}


int ftp_recv_ret(int ctl_fd, char *rcv_buf, int buf_len)
{
	int ret = 0;

	ret = tcp_recv(ctl_fd, rcv_buf, buf_len);
	if(ret == -1)
	{
		WRITELOG("recv error, [%d][%s]", errno, strerror(errno));
		return -1;
	}

	return ret;
}

int ftp_connect(char *ftp_host, unsigned short port)
{
	int ret = 0;
	int ctl_fd = -1;	
	struct sockaddr_in srv_addr;

	ctl_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(ctl_fd < 0)
	{
		WRITELOG("recv error, [%d][%s]", errno, strerror(errno));
		return -1;
	}

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	inet_aton(ftp_host, &srv_addr.sin_addr);

	struct timeval tm = {3, 0};
	setsockopt(ctl_fd, SOL_SOCKET, SO_SNDTIMEO, &tm, sizeof(tm));
	setsockopt(ctl_fd, SOL_SOCKET, SO_RCVTIMEO, &tm, sizeof(tm));
	/* 非阻塞的话，会很快返回正在处理的错误 */
	ret = connect(ctl_fd, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr));
	if(ret == -1)
	{
		WRITELOG("connect failed![%d][%s]", errno, strerror(errno));	
		return -1;
	}
	/* 有必要设置链接超时 */
	//unsigned long ul = 1;	
	//ret = ioctl(ctl_fd, FIONBIO, &ul);

	char ret_val[512] = {'\0'};
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);

	WRITELOG("connect OK!");
	return ctl_fd;
}

int ftp_login(int ctl_fd, const char *user, const char *pwd)
{
	int ret = 0;
	char ret_val[512] = {'\0'};

	ftp_send_cmd(ctl_fd, "%s %s\r\n", "USER", user);	
	WRITELOG("send over");
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);

	ftp_send_cmd(ctl_fd, "%s %s\r\n", "PASS", pwd);	
	WRITELOG("send over");
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);
	
	return 0;
}

int ftp_put(int ctl_fd, const char *file_name)
{
	int ret = 0;
	char ret_val[512] = {'\0'};

	ftp_send_cmd(ctl_fd, "%s\r\n", "PASV");
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);
	
	char *begin = strchr(ret_val, '(');
	if(begin == NULL)
	{
		WRITELOG("get '(' failed!");
		return -1;
	}
	begin++;
	char *end = strrchr(begin, ')');
	if(end == NULL)
	{
		WRITELOG("get ')' failed!");
		return -1;
	}
	*end = '\0';
	
	int a,b,c,d,h1,h2;
	WRITELOG("%s", begin);
	sscanf(begin, "%d,%d,%d,%d,%d,%d", &a,&b,&c,&d, &h1,&h2);
	unsigned short port = (h1 << 8) + h2;
	WRITELOG("data fd port: %d", port);

	int data_fd = ftp_connect("192.168.1.100", port);
	if(data_fd < 0)
	{
		WRITELOG("data fd connect failed...");
		return -1;
	}

	int fd = open(file_name, O_RDONLY);
	if(fd < 0)
	{
		WRITELOG("open file failed!..");
		return -1;
	}

	ftp_send_cmd(ctl_fd, "%s %s\r\n", "STOR", file_name);
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);

	char send_buf[1024] = {'\0'};
	while(1)
	{
		int ret = read(fd, send_buf, sizeof(send_buf));	
		if(ret > 0)
			tcp_send(data_fd, send_buf, ret);
		else 
			break;
		usleep(1000);	
	}
	close(fd);
	close(data_fd);
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);

	ftp_send_cmd(ctl_fd, "%s\r\n", "QUIT");
	ftp_recv_ret(ctl_fd, ret_val, sizeof(ret_val));
	WRITELOG("%s", ret_val);

	return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
		return -1;
	
	int ctl_fd = ftp_connect(argv[1], 21);
	WRITELOG("begin login!");

	ftp_login(ctl_fd, "joker", "fightforcs");

	ftp_put(ctl_fd, argv[2]);

	return 0;
}




