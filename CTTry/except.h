/**
 * \file except.h
 * \author  wzj
 * \brief 
 	1. simple try...catch... with setjmp longjmp
 * \version 
 * \note  
	1. 调用return 和 goto 的情况没有弄...
 	
 * \date: 2012年11月17日星期六14:00:11
 * 
 * discript your detail info.
 */ 
#ifndef _CT_EXCEPT_H_
#define _CT_EXCEPT_H_

#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>

typedef struct _ct_error_st{
	int 			err;
	char 			*err_str;
}ct_error_st;
/* exception jumper */
typedef struct _ct_except_st{
	jmp_buf 		env;			/**< jmp 句柄 */
	int 			ret_val;		/**< 跳转的返回值 */
	ct_error_st 	err;			/**< 错误的信息提示 */
	
	int				err_happend;	/**< 标记有没有错误发生 */
	int				err_catched;	/**< 如果错误被捕捉了，就不抛了 */
	struct _ct_except_st *prev;		/**< 为了支持错误一直向上级抛出 */
}ct_except_st;

int entry_try_area(ct_except_st *expt);
void throw_func(int err, char *str);
void leave_try_area(ct_except_st *expt);

#define TRY	{										\
				ct_except_st expt;					\
				expt.ret_val = setjmp(expt.env);	\
				if(!entry_try_area(&expt))			\
				{

#define CATCH(err) 									\
				} else if(err == expt.ret_val){		\
					expt.err_catched = 1;			

#define CATCH_ALL									\
				} else {							\
					expt.err_catched = 1;
					
#define FINAL	}									\
				{									\

#define ENDTRY	} 									\
				leave_try_area(&expt);				\
			}

#define THROW(err, str) do {						\
				throw_func(err, str);				\
				}while(0)

#endif
