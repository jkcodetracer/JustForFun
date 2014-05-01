/**
 * \file kebab.c
 * \author  wzj
 * \brief  this is my coroutine practise.
 *		the kebab ... is the Turkey babeq.
 * \version 
 * \note  
 * \date: 2013年07月20日星期六00:02:05
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ucontext.h>	/* the context switch api in the user level */
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include <Jlog.h>
#include "kebab.h"

#define MAX_KEBAB_QUEUE_SZ	(32)
#define MAX_KEBAB_STACK_SZ	(1024 * 1024)

struct _kebab_coroutine {
	coroutine_func func;		
	void *arg;
	ucontext_t ct;

	kebab_sched_st *pmng;
	
	int status;

	ptrdiff_t cap;
	ptrdiff_t size;
	char *stack;
};

struct _kebab_schedule {
	char stack[MAX_KEBAB_STACK_SZ];	
	ucontext_t main;

	int nroutine;
	int cap;
	int running;
	kebab_routine_st **queue;
};

static kebab_routine_st *_co_new(kebab_sched_st *psched,
								 coroutine_func func, 
								 void *ud)
{
	kebab_routine_st *proutine = calloc(1, sizeof(*proutine));	

	proutine->func = func;
	proutine->arg = ud;
	proutine->pmng = psched;
	proutine->cap = 0;
	proutine->size = 0;
	proutine->status = ROUTINE_READY;
	proutine->stack = NULL;

	return proutine;
}

static void _co_delete(kebab_routine_st *proutine)
{
	if (proutine->stack)
		free(proutine->stack);

	free(proutine);
}

kebab_sched_st *kebab_init(void)
{
	kebab_sched_st *psched = calloc(1, sizeof(*psched));		
	
	psched->nroutine = 0;
	psched->cap = MAX_KEBAB_QUEUE_SZ;
	psched->running = ROUTINE_MAIN;
	psched->queue = (kebab_routine_st**)calloc(1, 
					sizeof(kebab_routine_st*) * MAX_KEBAB_QUEUE_SZ);
	
	return psched;
}

void kebab_destroy(kebab_sched_st *psched)
{
	int i = 0;

	if (psched) {
		if (psched->queue) {
			for (i = 0;i < psched->cap; i++) {
				if(psched->queue[i] != NULL)	
					_co_delete(psched->queue[i]);
			}
			free(psched->queue);
		}
		free(psched);
	}
}

int kebab_new(kebab_sched_st *psched,
							coroutine_func func,
							void *arg)
{
	int pid = 0;
	kebab_routine_st *proutine = _co_new(psched, func, arg);

	if (psched->nroutine >= psched->cap) {
		pid = psched->nroutine;	
		psched->queue = (kebab_routine_st **)realloc(
						psched->queue, psched->cap * 2 * sizeof(void *));
		memset(psched->queue + psched->cap, 0, psched->cap * sizeof(void *));
		psched->queue[psched->cap] = proutine;
		psched->cap *=2;
		psched->nroutine ++;
	} else {
		int i;	
		for (i = 0;i < psched->cap; i++) {
			pid = (i+psched->nroutine)%psched->cap;	
			if (psched->queue[pid] == NULL) {
				psched->queue[pid] = proutine;	
				psched->nroutine++;
				break;	
			} 
		}
	}
	dblog("get new thread: %d", pid);
	return pid;
}

static void mainfunc(uint32_t low32, uint32_t hi32) 
{
	uintptr_t ptr = (uintptr_t)low32 | ((uintptr_t)hi32 << 32);
	kebab_sched_st *psched = (kebab_sched_st *)ptr;
	int id = psched->running;	
	kebab_routine_st *proutine = psched->queue[id];
	
	proutine->func(psched, proutine->arg);
	_co_delete(proutine);	
	psched->queue[id] = NULL;
	psched->nroutine --;
	psched->running = ROUTINE_MAIN;
}

void kebab_resume(kebab_sched_st *psched, int pid)
{
	if (psched->running != ROUTINE_MAIN) {
		dblog("main running error!");	
		return;
	}	

	if (pid < 0 || pid > psched->cap) {
		dblog("pid overflow!");	
		return ;
	}
	
	kebab_routine_st *proutine = psched->queue[pid];
	if (proutine == NULL) {
		dblog("the routine is not exist!");	
		return ;
	}	
	
	int status = proutine->status;
	uintptr_t ptr = (uintptr_t)psched;
	switch(status) {
		case ROUTINE_READY:	
			/* init the context */
			getcontext(&proutine->ct);
			proutine->ct.uc_stack.ss_sp = psched->stack;
			proutine->ct.uc_stack.ss_size = MAX_KEBAB_STACK_SZ;
			proutine->ct.uc_link = &psched->main;
			proutine->status = ROUTINE_RUNNING;

			psched->running = pid;
			/* set the routine's context */	
			makecontext(&proutine->ct, (void (*)(void))mainfunc, 2, 
					(uint32_t)ptr, (uint32_t)(ptr>>32));
			/* switch to the new routine */
			swapcontext(&psched->main, &proutine->ct);
			break;
		case ROUTINE_SUSPEND:
			/* restore the stack*/
			memcpy(psched->stack + MAX_KEBAB_STACK_SZ - proutine->size,
					proutine->stack, proutine->size);
			psched->running = pid;
			proutine->status = ROUTINE_RUNNING;
			swapcontext(&psched->main, &proutine->ct);
			break;	
		default:
			break;
	}

}
/* amazing time! 
	use the psched->stack as the public stack 
	when do the swith, we should store current 
	stack into the allocated room in the current toutine, 
	
	how to decide whitch part of the stack is the used part?
	we can allocate a local variable 'dummy', then it is the 
	the stack end..
*/
static void _save_stack(kebab_routine_st *proutine, char *top)
{
	char dummy = 0;	

	dblog("addr:%p\n", &dummy);
	if (proutine->cap < top - &dummy){
		if (proutine->stack)
			free(proutine->stack);	
				
		proutine->cap = top - &dummy;
		proutine->stack = calloc(1, proutine->cap);
	}

	proutine->size = top - &dummy;
	dblog("size:%d\n", proutine->size);
	memcpy(proutine->stack, &dummy, proutine->size);
}

void kebab_yield(kebab_sched_st *psched)
{
	int id = psched->running;
	kebab_routine_st *proutine = psched->queue[id];

	_save_stack(proutine, psched->stack + MAX_KEBAB_STACK_SZ);
	proutine->status = ROUTINE_SUSPEND;
	psched->running = ROUTINE_MAIN;
	swapcontext(&proutine->ct, &psched->main);
}

int kebab_status(kebab_sched_st *psched, int pid)
{
	if (pid < 0 || pid > psched->cap) {
		dblog("get kebab status failed! the pid is invalid!");	
		return 0;
	}
	
	if (psched->queue[pid] == NULL) {
		dblog("the [%d] is empty!", pid);	
		return ROUTINE_DEAD;
	}

	return psched->queue[pid]->status;
}

int kebab_running(kebab_sched_st *psched)
{
	return psched->running;
}




