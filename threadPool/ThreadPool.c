/*
 * @FileName: thread_pool.c
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
 * @Date: 2011年12月10日星期六21:22:27
 * 
 */ 

#include"ThreadPool.h"
#include"Jlog.h"
#include<stdlib.h>

static void* thread_com_func(void* args)
{
	int ret = 0;

	ASSERT(args != NULL, -1);

	J_single_thread* p_thread = (J_single_thread*)args;

	ret = pthread_detach(pthread_self());
	if(ret != 0)
	{
		ERRORLOG("thread detach failed");
		return ret;
	}
	
	while(1)
	{
		pthread_mutex_lock(&(p_thread->m_mutex));	
		WRITELOG("thread:%u wait for cond...", pthread_self());
		pthread_cond_wait(&(p_thread->m_cond), 
						  &(p_thread->m_mutex));
		pthread_mutex_unlock(&(p_thread->m_mutex));
		
		WRITELOG("On process!");
		p_thread->m_process_func;
		p_thread->m_used = 0;
	}

}

J_thread_pool *create_thread_pool(int min_num, int max_num)
{
	ASSERT(min_num <= max_num, -1);
	int i = 0;
	int ret = 0;
	J_single_thread* tmp_list = NULL;

	J_thread_pool* tmp_pool = (J_thread_pool*)malloc(sizeof(J_thread_pool));
	if(tmp_pool == NULL)
	{
		WRITELOG("malloc thread pool failed");
		return -1;
	}
	
	memset((char*)tmp_pool, 0, sizeof(J_thread_pool));
	tmp_pool->min_num = min_num;
	tmp_pool->max_num = max_num;
	
	tmp_list = (J_single_thread*)malloc(sizeof(J_single_thread)*min_num);
	if(tmp_list == NULL)
	{
		WRITELOG("malloc thread list failed");
		free(tmp_pool);
		return -1;
	}
	tmp_pool->thread_pool = tmp_list;

	for(i = 0; i < min_num; i++)
	{
		tmp_list[i].m_used = 0;
		tmp_list[i].m_process_func = NULL;
		ret = pthread_mutex_init(&(tmp_list[i].m_mutex), NULL);
		if(ret != 0)
		{
			ERRORLOG("init mutex failed: %d", ret);	
			free(tmp_list);
			free(tmp_pool);
			return ret;
		}
		ret = pthread_cond_init(&(tmp_list[i].m_cond), NULL);
		if(ret != 0)
		{
			ERRORLOG("init cond failed: %d", ret);
			free(tmp_list);
			free(tmp_pool);
			return ret;
		}
		ret = pthread_create(&(tmp_list[i].m_thread), NULL,  
								thread_com_func, &(tmp_list[i]));
		if(ret != 0)	
		{
			ERRORLOG("init thread failed: %d", ret);
			free(tmp_list);
			free(tmp_pool);
			return ret;
		}
	}
	tmp_pool->current_num = min_num;
			free(tmp_list);
			free(tmp_pool);
			return ret;
}

int J_pool_deal_job(J_thread_pool* thiz, J_process_func new_job)
{
	int ret = 0;
	int i = 0;
	ASSERT((thiz != NULL)&&(new_job != NULL), -1);
	
	for(i = 0;i < thiz->current_num; i++)
	{
		if(thiz->thread_pool[i].m_used == 0)
		{
			WRITELOG("%d is for you!", i);
			pthread_mutex_lock(&(thiz->thread_pool[i].m_mutex));
			thiz->thread_pool[i].m_process_func = new_job;
			thiz->thread_pool[i].m_used = 1;
			pthread_mutex_unlock(&(thiz->thread_pool[i].m_mutex));
			pthread_cond_broadcast(&(thiz->thread_pool[i].m_cond));
			break;
		}
	}

	if(i >= thiz->current_num)
	{
		WRITELOG("No enough thread for you..");	
		ret = -1;	
	}

	return ret;
}

int J_pool_exit(J_thread_pool* thiz)
{
	ASSERT(thiz != NULL, -1);
	int i = 0;

	if(thiz->thread_pool != NULL)
	{
		for(i = 0; i < thiz->current_num; i++)
		{
			pthread_kill(thiz->thread_pool[i].m_thread, SIGQUIT);
			pthread_mutex_destroy(&(thiz->thread_pool[i].m_mutex));
			pthread_cond_destroy(&(thiz->thread_pool[i].m_cond));
		}
		free(thiz->thread_pool);
		thiz->thread_pool = NULL;
	}

	free(thiz);
	thiz = NULL;

	return 0;
}
