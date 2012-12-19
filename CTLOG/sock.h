/**
 * \file sock.h
 * \author  wzj
 * \brief simple socket interface
 * \version 1.0
 * \note  
 * \date: 2012年08月04日星期六12:41:19
 * 
 */ 
#ifndef CT_SOCKET_H 
#define CT_SOCKET_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

/**
 * \brief create unix domain socket
 * \param sock_path the socket path 
 * \param [out] sock_addr the socket resource
 * \return sock_fd 
 *		 -1 failed
 */
int un_sock_init(const char *sock_path, struct sockaddr_un *sock_addr);

/**
 * \brief bind the socket 
 * \param 
 */

/**
 * \brief close the sock fd
 * \param fd sock fd
 * \return 0 success
 *      -1 failed
 */
int un_sock_close(int fd);


#endif
