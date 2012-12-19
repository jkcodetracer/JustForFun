/**
 * \file logs.h
 * \author  wzj
 * \brief simple log system
 * \version 1.0
 * \note  
 * \date: 2012年08月04日星期六10:48:36
 * 
 * discript your detail info.
 */ 

#ifndef _CT_COMMON_LOG_LOGS_H
#define _CT_COMMON_LOG_LOGS_H

/* common lib */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <execinfo.h>		/**< for back trace */

#define CT_LOGD_UN_PATH		"/home/joker/alllog.un"			/**< un back path */

#define MAX_LOG_BUFFER	(2048)	/* buffer log size */

/**
 * time stamp
 */
typedef struct _ct_time_st{
	int sec;		/**< seconds */
	int min;		/**< minutes */
	int hour;		/**< hours */
	int day;		/**< day of the month */
	int month;		/**< month */
	int year;		/**< year */
}ct_time_st;

/**
 * log frame, communication used by process log.
 */
typedef struct _log_frame_st{
	int log_type;
	ssize_t pid;
	ct_time_st time_stamp;	
	char log_buffer[MAX_LOG_BUFFER];
}log_frame_st; 

/**
 * log type 
 */
enum _log_type_t{
	LOG_REAL = 0x01,			/**< real time logs. */		
	LOG_DEBUG = 0x02,			/**< debug logs. */
	LOG_ERR = 0x04,				/**< error logs. */
	LOG_ALARM = 0x08,			/**< alarm logs. */
};

/**
 * \brief log init 
 * \param thr_nm the name of of the thread/process
 * \param log_res the resources for special use.
 * \return 0 success
 * 		   !0 failed
 *
 * it will create a new thread, to send logs to the logd
 */
int log_init(const char *thr_nm, const char *log_res);

/**
 * \brief log_release
 * 
 * release all the resources the logs own
 */
void log_release();

/**
 * \brief log_writer
 * \param fd the fd you want to put, if -1, default dump to the stdout
 * \param fmt the varable param
 * \param type log type
 * \return 0 success
 *		   other the errno
 */
int log_writer(int fd, int type, const char *fmt, ...);

extern int g_debug;
/**
 * if in debug mode , all dump to the stdout. 
 * otherwise dump to the global fd, which log_init set.
 */
#define LOGREAL(fmt, args...) do{	\
			if(g_debug & LOG_REAL){log_writer(0, LOG_REAL,"r [%s:%s:%d]"fmt"\n", __FILE__, __func__, __LINE__, ##args);} \
			}while(0) 

#define LOGDEBUG(fmt, args...) do{	\
			int tmpfd = (g_debug & LOG_DEBUG)?0:-1;	\
			if(g_debug & LOG_DEBUG){log_writer(tmpfd, LOG_DEBUG, "d [%s:%s:%d]"fmt"\n", __FILE__, __func__, __LINE__, ##args);}	\
		}while(0)

#define LOGALARM(fmt, args...) do{	\
			int tmpfd = (g_debug)?0:-1;	\
			log_writer(tmpfd, LOG_ALARM, "alarm: [%s:%s:%d]"fmt"\n", __FILE__, __func__, __LINE__, ##args);\
		}while(0)

#define LOGERROR(fmt, args...) do{	\
			int tmpfd = (g_debug)?0:-1;	\
			log_writer(tmpfd, LOG_ERR, "error: [%s:%s:%d]"fmt"\n", __FILE__, __func__, __LINE__, ##args);\
		}while(0)
/* you can dump log to the file by set the filename. */
#define ASSERT(p, ret_val) do{	\
			int tmpfd = (g_debug)?0:-1;	\
			int stack_lvl = 0;	\
			int i = 0;	\
			char info_buf[1024] = {'\0'};	\
			void *stack_buf[5];		\
			char **symbol = NULL;	\
			stack_lvl = backtrace(stack_buf, 5);	\
			symbol = backtrace_symbols(stack_buf, stack_lvl);	\
			for(i = 0; i < stack_lvl; ++i)		\
			{ strcat(info_buf, symbol[i]); strcat(info_buf, "\n");}	\
			if(!(p)){log_writer(tmpfd, 0, "[%s:%s:%d]( "#p" ) assert failed!\n%s", __FILE__, __func__, __LINE__, info_buf);return ret_val;}	\
		}while(0)	

#endif
