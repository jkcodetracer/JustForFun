/**
 * \file event_test.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年05月29日星期三22:32:30
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <fcntl.h>

#include <event.h>

void fifo_read(int fd, short event, void *arg)
{
	char buf[255] = {'\0'};
	int len = 0;	
	struct event *ev = arg;
	
	len = read(fd, buf, sizeof(buf) - 1);	
	if (len == -1) {
		perror("read");	
		return ;
	} else if (len == 0) {
		fprintf(stderr, "Connection closed\n");	
		return ;
	}

	buf[len] = '\0';
	fprintf(stdout, "Read: %s\n", buf);

	event_add(ev, NULL);
}

int main(int argc, char *argv[])
{
	struct event evfifo; 
	struct stat st;
	const char *fifo = "my.fifo";
	int socket;

	if (lstat(fifo, &st) == 0) {
		if ((st.st_mode & S_IFMT) == S_IFREG) {
			errno = EEXIST;	
			perror("lstat");
			exit(1);
		}	
	}
	
	unlink(fifo);
	if (mkfifo(fifo, 0777) == -1) {
		perror("mkfifo");	
		exit(1);
	}
	
	socket = open(fifo, O_RDWR | O_NONBLOCK, 0);
	if (socket == -1) {
		perror("open");	
		exit(1);
	}

	fprintf(stderr, "write data to %s\n", fifo);

	/* init the event library! */
	event_init();
	/* initialize one event! */
	event_set(&evfifo, socket, EV_READ, fifo_read, &evfifo);

	/* add it to the active events. without timeout! */	
 	event_add(&evfifo, NULL);	
	/* begin monitor */	
	event_dispatch();

	return 0;
}
