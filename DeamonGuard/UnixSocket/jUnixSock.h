/*
 * @FileName: jUnixSock.h
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
 * @Date: 2012年03月25日星期日22:49:28
 * 
 */ 
#ifndef J_UNIX_SOCKET_FOR_DEAMON
#define J_UNIX_SOCKET_FOR_DEAMON
/*
* create a unix socket
*/
int create_unix_sock(const char* sock_path);

/*
* set a unix socket
*/


/*
* close a unix socket
*/
int close_unix_sock(int sock_fd);

#endif
