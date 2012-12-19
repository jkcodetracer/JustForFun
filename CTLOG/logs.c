/**
 * \file logs.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月04日星期六10:48:32
 * 
 */ 
#include "logs.h"
#include "sock.h"

int g_debug = 1;						/**< debug flag */
static int g_log_fd = 0;				/**< the fd for un_sock, to send logs to logd. */
static struct sockaddr_un g_un_addr;	/**< to send logs to the logd. */
socklen_t sock_len = 0;					

int log_init(const char *thr_nm, const char *log_res)
{
	int fd = -1, ret = 0;
	
	fd = un_sock_init(CT_LOGD_UN_PATH, &g_un_addr);
	if(ret == -1)
	{
		LOGALARM("init un sock failed!");
		return -1;
	}
	
	g_log_fd = fd;
	sock_len = strlen(g_un_addr.sun_path) + sizeof(g_un_addr.sun_family);

	return 0;
}

void log_release()
{
	un_sock_close(g_log_fd);	
}

int log_writer(int fd, int type, const char *fmt, ...)
{
	int ret = 0;
	va_list ap;
	char log_buf[sizeof(log_frame_st)] = {'\0'};
	log_frame_st *pframe = (log_frame_st* )log_buf;

	if(fd == -1)
	{	/* TODO global fd */
		//fd = stdout;
	}

	pframe->log_type = type;
	pframe->pid = getpid();

	va_start(ap, fmt);
	ret = vsnprintf(pframe->log_buffer, sizeof(pframe->log_buffer), fmt, ap);
	va_end(ap);

	ret = write(fd, pframe->log_buffer, sizeof(pframe->log_buffer));

	if(g_log_fd > 0)
	{	/* send log to logd. */
		ret = sendto(g_log_fd, pframe, sizeof(log_frame_st), 0, (struct sockaddr*)&g_un_addr, sock_len);
		printf("%d = ..\n",ret);
	}

	return ret;
}
#if 0
int test2(int a, int b)
{
	ASSERT(a && b, -1);
	return 0;
}

int test1(int a, int b)
{
	test2(a, b);
	return 0;
}
#endif

#ifdef DEBUG
/* for test. */
int main()
{
	int a = 0;
	int b = 123;
	log_init(NULL, NULL);
	LOGREAL("this is for test %s..", "just for test");
	LOGDEBUG("debug...%d ", 123);
	LOGALARM(" alarm...%d ", 333);
	LOGERROR("error...%s", "nothing");
	ASSERT(a == b,-1);
	ASSERT(a != b, -1);
	ASSERT(a > b, -3);

//	test1(a,b);

	return 0;	
}
#endif








