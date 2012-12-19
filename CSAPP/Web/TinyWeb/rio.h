/*
 * @FileName: rio.h
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
 * @Date: 2012年05月24日星期四07:30:21
 * 
 */ 

#ifndef _RIO_IO_H_
#define _RIO_IO_H_

#include <sys/types.h>
#define RIO_BUFSIZE		(8192)


typedef struct{
	int rio_fd;			//decriptor for this internal buf
	int rio_cnt; 		//unread bytes in internal buf
	char *rio_bufptr;	//next unread byte in internal buf
	char rio_buf[RIO_BUFSIZE];	//internal buffer
}rio_t;

ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
void rio_initb(rio_t *rp, int fd);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

#endif
