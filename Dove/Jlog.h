/*
 * @FileName: Jlog.h
 * @Author: wzj 
 * @Brief: 
 *  1.simple log  
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

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<execinfo.h>

#ifdef CTDEBUG

#define WRITELOG(fmt, args...)	do {	\
		printf("%s:%s:%d:"fmt"\n",__FILE__, __func__, __LINE__, ##args);	\
		}while(0)

#define ERRORLOG(fmt, args...)	do {	\
		printf("%s:%s:%d:"fmt"\nerromsg:%d:%s\n",__FILE__, __func__,\
		__LINE__, ##args, errno, strerror(errno));	\
		}while(0)

#define ASSERT(p, ret) 	if(!(p))	\
		{printf("%s:%s:%d Warning: "#p" failed.\n",	\
			__FILE__,__func__, __LINE__);	\
			int stack_level = 0;		\
			int i = 0;		\
			void *stack_buf[10];		\
			char **symbol = NULL;		\
			stack_level = backtrace(stack_buf, 10);		\
			symbol = backtrace_symbols(stack_buf, stack_level);			\
			for(i = 0; i < stack_level; i++)		\
			{		\
				printf("%s\n", symbol[i]);		\
			}		\
			free(symbol);		\
			return (ret);}

#define DUMPLOG(file, fmt, args...)  do {		\
			FILE* fp = fopen(file, "a+");	\
			struct stat fst;		\
			if(stat(file, &fst))break; 	\
			if(fst.st_size > 1024 *16) {	\
				if(ftruncate(fileno(fp), 0))break;}		\
			fprintf(fp, "[%s:%s:%d:]"fmt"\n", __FILE__, __func__, __LINE__, ##args);	\
			fflush(fp);	fclose(fp);	}while(0)		

#else

#define WRITELOG(fmt, args...) do{;} while(0)
#define ERRORLOG(fmt, args...) do{;} while(0)
#define ASSERT(p, ret)  do{;} while(0)
#define DUMPLOG(fmt, args...) do{;} while(0)

#endif
#endif




