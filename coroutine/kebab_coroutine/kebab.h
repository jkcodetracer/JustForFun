/**
 * \file kebab.h
 * \author  wzj
 * \brief  let's have a taste with the coroutine
 *		
 * \version 
 * \note  
 * \date: 2013年07月20日星期六00:06:07
 */ 

#ifndef _FUNNEY_KEBAB_COROUTINE_H_
#define _FUNNEY_KEBAB_COROUTINE_H_


enum {
	ROUTINE_DEAD = -2,
  	ROUTINE_MAIN = -1,
   	ROUTINE_READY = 0,
   	ROUTINE_SUSPEND,
	ROUTINE_RUNNING
};

/* the coroutine member */
typedef struct _kebab_coroutine kebab_routine_st;
/* the coroutine manager */
typedef struct _kebab_schedule kebab_sched_st;

typedef void* (*coroutine_func)(kebab_sched_st *pshced, void *arg);

/**
 * \brief init the coroutine manager.
 * \return kebab_sched_st* 
 */
kebab_sched_st *kebab_init(void);

/**
 * \brief destroy the coroutine manager
 */
void kebab_destroy(kebab_sched_st *psched);

/**
 * \brief add a new routine into the manager.
 * \param psched: the manager pointer
 * 		  func:	 the coroutine function
 *		  arg:  the coroutine argument.
 *	\return pid the new coroutine pid.
 */
int kebab_new(kebab_sched_st *psched, coroutine_func func, void *arg);

/**
 * \brief resume the No.pid routine
 * \param psched the coroutine manager
 * 		  pid the routine id
 */
void kebab_resume(kebab_sched_st *psched, int pid);


/**
 * \brief the sub routine yield the context to the main
 * \param psched the coroutine manager
 */
void kebab_yield(kebab_sched_st *psched);

/**
 * \brief get the status of the No.pid routine.
 * \param psched the coroutine manager
 * 		  pid the routine's id	
 */
int kebab_status(kebab_sched_st *psched, int pid);

/**
 * \brief get who is running now.
 * \note if the main is running, while return -1;
 */
int kebab_running(kebab_sched_st *psched);

#endif //end for the _FUNNEY_KEBAB_COROUTINE_H_

