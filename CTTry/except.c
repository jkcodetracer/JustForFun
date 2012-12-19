/**
 * \file except.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年11月17日星期六14:00:15
 * 
 * discript your detail info.
 */ 
#include <stdlib.h>
#include <Jlog.h>
#include "except.h"

static ct_except_st *s_except = NULL;
/* 进入try区域，需要设定跳转点 */
int entry_try_area(ct_except_st *expt)
{
	ASSERT(expt != NULL, -1);
	
	if(!expt->ret_val)
	{
		expt->prev 			= s_except;
		expt->err.err 		= 0;
		expt->err.err_str 	= NULL;
		expt->err_happend	= 0;
		expt->err_catched 	= 0;
		s_except 			= expt;	
	} else {
		s_except = expt->prev;		/* 回到上一级的异常捕捉点 */		
	}

	return expt->ret_val;
}
/* 异常抛出函数 */
void throw_func(int err, char *str)
{
	ASSERT_EXIT(s_except != NULL);

	s_except->err.err 		= err;
	s_except->err.err_str 	= str;
	s_except->err_happend 	= 1;

	if(!str){
		dblog("throw error, [%d]", err);
	} else {
		dblog("throw error, [%d][%s]", err, str);	
	}
	
	longjmp(s_except->env, s_except->err.err);
}
/* 离开一块try区域，主要处理多级函数抛出异常的情况 */
void leave_try_area(ct_except_st *expt)
{
	/* 没有被捕捉，就继续抛出异常 */
	if(s_except != NULL  && 
	   expt->err_happend &&
	   !expt->err_catched)
	{
		throw_func(expt->err.err, expt->err.err_str);
	}
}

void throw_one()
{
	dblog("in throw once");
	THROW(1, "throw one on!");
}

int throw_test()
{
	dblog("in throw test!");
	TRY{
		throw_one();
	} CATCH(1){
		dblog("throw once!");	
	} 
	ENDTRY
	
	return 0;
}

int main(int argc, char *argv[])
{
	int i = 0;
#if 0
	TRY{
		if(i == 0)	
			THROW(1, "i is zero");
	} CATCH(1){
		i++;	
	}
	FINAL {
		dblog("first time done!");	
	}
	ENDTRY

	TRY{
		if(i == 0)
			THROW(1, "i is zero");
	} CATCH(1){
		i++;	
	}
	FINAL {
		dblog("second time done!");	
	}
	ENDTRY
#endif

	TRY{
		throw_test();	
	} CATCH(1){
		dblog("throw twice!");
	}
	FINAL {
		dblog("third the inside function error!");	
	}
	ENDTRY

	dblog("final i is [%d]", i);

	return 0;
}

