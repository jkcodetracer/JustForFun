/*
 * @FileName: thread_pool.h
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
 * @Date: 2011年12月10日星期六21:14:31
 * 
 */ 
#include<stdio.h>
#include<pthread.h>
#include<signal.h>

typedef struct J_thread_pool_s J_thread_pool;
typedef struct J_single_thread_s J_single_thread;
typedef void* (*J_process_func)()	;

struct J_single_thread_s{
	int 			m_used;
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_cond;
	pthread_t		m_thread;
	J_process_func	m_process_func;
};

struct J_thread_pool_s{
	int max_num;
	int min_num;
	int current_num;
	int rest_num;
	J_single_thread* thread_pool;
};

J_thread_pool *create_thread_pool(int min_mum, int max_mum);
