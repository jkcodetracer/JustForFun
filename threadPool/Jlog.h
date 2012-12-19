/*
 * @FileName: Jlog.h
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
 * @Date: 2011年12月11日星期日13:23:11
 * 
 */ 
#ifndef _J_LOG_H
#define _J_LOG_H

#include<errno.h>
#include<string.h>

#define WRITELOG(fmt, args...)	do {	\
		printf("%s:%s:%d:"fmt"\n",__FILE__, __func__,__LINE__,##args);	\
		}while(0)

#define ERRORLOG(fmt, args...)	do {	\
		printf("%s:%s:%d:"fmt"\nerromsg:%d:%s\n",__FILE__, __func__,\
		__LINE__,##args, errno, strerror(errno));	\
		}while(0)

#define ASSERT(p, ret) 	if(!(p))	\
		{printf("%s:%s:%d Warning: "#p" failed.\n",	\
			__FILE__,__func__, __LINE__);return (ret);}
		

#endif
