/*
 * @FileName: rio.c
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
 * @Date: 2012年05月24日星期四07:32:30
 * 
 */ 
#include "rio.h"

ssize_t 
rio_readn(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;

	while(nleft > 0){
		if((nread = read(fd, bufp, nleft)) < 0){
			if(errno == EINTR 	|| 
			   errno == EAGAIN 	||		//nonblock
			   errno == EWOULDBLOCK)	//nonblock
				nread = 0;		//call again
			else 
				return -1;
		} else if(nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}

	return (n-nleft);
}

ssize_t 
rio_writen(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = usrbuf;

	while(nleft > 0) {
		if((nwritten = write(fd, bufp, nleft)) <= 0){
			if(errno == EINTR	||
			   errno == EAGAIN	||
			   errno == EWOULDBLOCK)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwrittent;
		bufp += nwritten;
	}

	return n;
}
//buffered IO  to improve the speed?
static ssize_t 
rio_read(rio_t *rp, char *usrbuf, size_t n)
{
	int cnt;

	while (rp->rio_cnt  <= 0){
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, 
						sizeof(rp->rio_buf));

		if(rp->rio_cnt < 0){
			if(errno != EINTR &&
			   errno != EAGAIN &&
			   errno != EWOULDBLOCK)
			{ 
				return -1;
			} else if(rp->rio_cnt == 0) {
				return 0;
			} else {
				rp->rio_bufptr = rp->rio_buf;
			}
		} 
	}

	cnt = n;
	if (rp->rio_cnt < n)
		cnt = rp->rio_cnt;
	memcpy(usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->cnt -= cnt;

	return cnt;
}

void
rio_readinitb(rio_t *rp, int fd)
{
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_buffer = rp->rio_buf;
}

ssize_t 
rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;
	
	while(nleft > 0) {
		if ((nread = rio_readn(rp, bufp, nleft)) < 0)	
		{
			if(errno == EINTR ||
			   errno == EAGAIN ||
			   errno == EWOULDBLOCK)
			{ //线程不安全
				nread = 0;
			} else {
				return -1;
			}
		} else if(nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}

	return (n-nleft);
}

ssize_t
rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
	int n, rc;
	char c, *bufp = usrbuf;
	//要加入\0 所以要留一个
	for(n = 1; n < maxlen ; n++){
		if((rc = rio_read(rp, &c, 1)) == 1){
			*bufp++ = c;
			if(c == '\n')
				break;
		} else if (rc == 0) {
			if(n == 1)	
				return 0;	//空字符串
			else 
				break;
		} else  
			return -1;
	}

	*bufp = 0;
	return n;
}
