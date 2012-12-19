/*
 * @FileName: main.c
 * @Author: wzj
 * @Brief:  tiny web server...
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月27日星期日14:38:05
 * 
 */ 

#include "sock_i.h"
#include <strings.h>

#define MAXLINE		(1024)

void doit(int fd);
void read_requesthdrs(rio_t *p);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *url, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);

int 
main(int argc, char **argv)
{
	int listenfd, connfd, port, clientlen;
	struct sockaddr_in clientaddr;
	
	if(argc != 2){
		fprintf(stderr, "usage: %s <port>\n\n", argv[0]);
		return -1;
	}

	port = atoi(argv[1]);

	listenfd = open_listenfd(port);
	while(1){
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		doit(connfd);
		close(connfd);
	}	

	return 0;
}

void 
doit(int fd)
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE];
	char filename[MAXLINE],cgiargs[MAXLINE];
	rio_t rio;
	
	rio_initb(&rio, fd);
	rio_readlineb(&rio, buf, MAXLINE);
	sscanf(buf, "%s %s %s", method, uri, version);
	if(strcasecmp(method, "GET")){
		clienterror(fd, method, "501", "Not Implemented",
				"Tiny does not implement this method");
		return;
	}

	read_requesthdrs(&rio);

	is_static = parse_uri(uri, filename, cgiargs);
	if(stat(fiename, &sbuf) < 0) {
		clienterror(fd, filename, "404", "Not found",
					"Tiny couldn't find this file");
		return;
	}
	//get a page ...
	if(is_static){ //S_ISREG ragular file
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
			clienterror(fd, filename, "403", "Forbidden", 
						"Tiny couldn't read the file");
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
	} 
}

void 
clienterror(int fd, char *cause, char *errnum, 
			char *shortmsg, char *longmsg)
{
	char buf[MAXLINE], body[MAXLINE];	

	sprintf(body, "<html><title>Tiny Error</title>");
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n",body);
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s:%s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>THe Tiny Web server</em>\r\n", body);
	
	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", strlen(body));
	rio_writen(fd, buf, strlen(buf));
	rio_writen(fd, body, strlen(body));
}

void 
read_requesthdrs(rio_t *rp)
{
	char buf[MAXLINE];

	rio_readlineb(rp, buf, MAXLINE);
	while(strcmp(buf, "\r\n"))
		rio_readlineb(rp, buf, MAXLINE);
	
	return;
}

//这个url . 应该是只含有根目录以及后面
//那一部分的，没有域名的
int 
parse_uri(char *url, char *filename, char *cgiargs)
{
	char *ptr;

	if(!strstr(uri, "cgi-bin"))
	{
		strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		if(uri[strlen(uri) - 1] == '/')
			strcat(filename, "home.html");
		return 1;
	} else {
		ptr = index(uri, '?');
		if(ptr) {
			strcpy(cgiargs, ptr + 1);
			*ptr = '\0';
		} else 
			strcpy(cgiargs, "");

		strcpy(filename, ".");
		strcat(filename, uri);
		return 0;
	}
}
//static file
void 
serve_static(int fd, char *filename, int filesize)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXLINE];

	get_filetpye(filename, filetype);
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
	sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
	rio_writen(fd, buf, strlen(buf));

	srcfd = open(filename, O_RDONLY, 0);
	//把文件加载到内存 为什么这样加载?比较快！
	srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	close(srcfd);
	rio_write(fd, srcp, filesize);
	munmap(srcp, filesize);
}
//得到文件类型，是为了填写http报文
void 
get_filetype(char *filename, char *filetype)
{
	if(strstr(filename, ".html"))	
		strcpy(filetype, "text/html");
	else if(strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");
	else if(strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpg");
	else 
		strcpy(filetype, "text/plain");
}

void
serve_dynamic(int fd, char *filename, char *cgiargs)
{
	char buf[MAXLINE], *emptylist[] = {NULL};

	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	rio_writen(fd, buf, strlen(buf));

	if (fork() == 0) {
	//用环境变量传参数.... 真正的服务器，还设置其他变量。
		setenv("QUERY_STRING", cgiargs, 1);
		dup2(fd, stdout);
		execve(filename, emptylist, environ);
	}

	wait(NULL);
}
	
