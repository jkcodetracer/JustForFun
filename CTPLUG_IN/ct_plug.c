/**
 * \file ct_plug.c
 * \author  wzj
 * \brief  尝试一下hook函数
 * \version 
 * \note  
 * \date: 2012年08月26日星期日13:25:23
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "../Jlog.h"

#define SAFEFREE(p) 	if(!(p)){	\
			free(p), p = NULL;	\
		}

/**
 * hook function
 */
typedef void* (*hook_func_t)(void *in, void *cont);
/**
 * hook struct  以链表的形式保存
 */
typedef struct _simple_hook_st{
	char name[128];
	hook_func_t hook_func;	
	struct _simple_hook_st *next;
}simple_hook_st;

/**
 * hook manager 管理者 
 */
typedef struct _hook_manager_st{
	char name[128];	
	simple_hook_st *hook_list;
}hook_manager_st;

int hook_manager_init(hook_manager_st **pmanager, char *name)
{
	*pmanager = (hook_manager_st*) calloc(1, sizeof(hook_manager_st));
	if(*pmanager == NULL){
		WRITELOG("alloc manager failed!");	
		return -1;
	}

	snprintf((*pmanager)->name, 128, "%s", name);
	WRITELOG("init hook manager: %s", name);

	return 0;
}

int hook_plug_init(simple_hook_st **phook, hook_func_t pfunc, char *name)
{
	*phook = (simple_hook_st*)calloc(1, sizeof(simple_hook_st));
	if(*phook == NULL){
		WRITELOG("calloc simple hook st failed!");	
		return -1;
	}

	snprintf((*phook)->name, 128, "%s", name);
	(*phook)->hook_func = pfunc;
	WRITELOG("init plug [%s] OK!", name);	
	
	return 0;
}

int hook_regist(hook_manager_st *pmanager, simple_hook_st *phook)
{
	ASSERT(pmanager != NULL && phook != NULL, -1);
	/* 找找看，插件在不在，在了不允许插入 */
	simple_hook_st *walk_hook = NULL;
	for(walk_hook = pmanager->hook_list; walk_hook != NULL; walk_hook = walk_hook->next)
	{
		if(!memcmp(walk_hook->name, phook->name, 128))
		{
			WRITELOG("The plug has already exist!");	
			return -1;
		}
	}

	/* TODO 上锁 */	
	phook->next = pmanager->hook_list;
	pmanager->hook_list = phook;
	
	return 0;
}

int hook_unregist(hook_manager_st *pmanager, const char *name)
{
	ASSERT(pmanager != NULL && name != NULL, -1);	

	simple_hook_st *phook = NULL;
	simple_hook_st *prev = NULL;

	WRITELOG("do unhook!");
	
	for(phook = pmanager->hook_list; phook != NULL; prev = phook, phook = phook->next)
	{
		WRITELOG("hook name [%s]", phook->name);
		if(!strcmp(phook->name, name))
		{
			if(prev == NULL)
			{
				pmanager->hook_list = phook->next;	
			} else {
				prev->next = phook->next;	
			}
			WRITELOG("find the hook!");
			break;
		}
	}

	SAFEFREE(phook);
	
	return 0;
}

int hook_point(hook_manager_st *pmanager)
{
	ASSERT(pmanager != NULL, -1);
	
	simple_hook_st *phook = NULL;

	phook = pmanager->hook_list;

	while(phook != NULL)
	{	/* TODO param  and lock */
		if(phook->hook_func != NULL)	
			phook->hook_func(NULL, NULL);
		phook = phook->next;
	}
	
	return 0;
}

int hook_manager_destroy(hook_manager_st *pmanager)
{
	ASSERT(pmanager != NULL, -1);

	simple_hook_st *phook = NULL;
	simple_hook_st *next = NULL;
	
	phook = pmanager->hook_list;
	while(phook != NULL)
	{
		next = phook->next;
		WRITELOG("unregist hook: [%s]", phook->name);
		SAFEFREE(phook);
		phook = next;
	}

	SAFEFREE(pmanager);

	return 0;
}

int hook_plug_destroy(simple_hook_st *phook)
{
	SAFEFREE(phook);

	return 0;
}


#ifdef CTDEBUG

void *print_plug(void *message, void *cont)
{
	printf("this is a print plug...\n");

	return NULL;
}

int a = 100;
int b = 200;

void *add_plug(void *in, void *cont)
{
	int c = a + b;	

	printf("add_plug: %d + %d = %d",a, b, c);

	return NULL;
}


int main()
{
	hook_manager_st *pmanager;	
	int ret = 0;	
	
	ret = hook_manager_init(&pmanager, "code tracer");
	if(ret != 0)
	{
		WRITELOG("init manager failed!");	
		return -1;
	}

	simple_hook_st *pplug_print = NULL;
	ret = hook_plug_init(&pplug_print, print_plug, "print plug");
	if(ret != 0)
	{
		WRITELOG("init print plug failed!");	
		/*mem leak */
		return -1;
	}

	simple_hook_st *pplug_add = NULL;
	ret = hook_plug_init(&pplug_add, add_plug, "add plug");
	if(ret != 0)
	{
		WRITELOG("init add plug failed!");	
		/*mem leak */
		return -1;
	}

	ret = hook_regist(pmanager, pplug_add);	
	ret = hook_regist(pmanager, pplug_print);

	int i = 0;
	while(1)
	{
		i++;
		if(i > 10)
		{
			WRITELOG("over exit!");	
			break;
		}

		hook_point(pmanager);
	}
	
	ret = hook_unregist(pmanager, "add plug");
	if(ret == 0)
	{
		WRITELOG("unregist [%s] success!", "add plug");
	}

	ret = hook_unregist(pmanager, "print plug");
	if(ret == 0)
	{
		WRITELOG("unregist [%s] success!", "print plug");
	}

	hook_manager_destroy(pmanager);
		
	return 0;
}

#endif //CTDEBUG





