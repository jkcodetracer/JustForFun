/**
 * \file pipeline.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月23日星期四21:06:19
 * 
 * discript your detail info.
 */ 

#include <stdlib.h>
#include <stdio.h>

#include "Jlog.h"
#include "pipeline.h"

typedef struct _pipe_count_st{
	int total_len;
}pipe_count_st;
/**
 * for get all pipe line len
 */
static void* pipe_len_walk(hash_node_st *node, void *cont)
{
	pipe_count_st *pcount = (pipe_count_st*)cont;
	ct_pipeline_st *ppipe = (ct_pipeline_st*)(node->data);

	pcount->total_len += ppipe->pipe_len + sizeof(chunk_ring_st);

	WRITELOG("pipe len: %d, chunk_len: %d", ppipe->pipe_len, sizeof(chunk_ring_st));

	return (void*)pcount;
}
/** 
 * \brief alloc pipe with space
 */
static void* pipe_alloc_walk(hash_node_st *node, void *cont)
{
	int total_len = 0;
	ct_pipeline_st *ppipe = (ct_pipeline_st*)(node->data);
				
	ppipe->pipe = chunk_ring_init(ppipe->pipe_name,
								 (char*)cont,
								 ppipe->pipe_len);
	if(ppipe->pipe == NULL)
	{
		WRITELOG("alloc space to pipe failed!");	
		return NULL;
	}
	
	total_len = sizeof(chunk_ring_st) + ppipe->pipe_len;	

	WRITELOG("pipe: %s alloced: %d", ppipe->pipe_name, total_len);

	return cont + total_len;
}
/**
 * \brief hire workers 
 */
static void *hire_worker(hash_node_st *node, void *cont)
{
	int i = 0, ret = 0;
	pid_t pid = 0;
	chunk_ring_st *in = NULL, *out = NULL;
	ct_boss_st *pboss = (ct_boss_st *) cont;
	ct_job_st *pjobs = (ct_job_st *) node->data;

	if(pjobs->in[0] != '\0')
	{
		ret = hash_search(pboss->pipelines, pjobs->in, strlen(pjobs->in), &(void*)in);	
		if(ret != 0)
		{
			WRITELOG("search [%s] pipeline failed!", pjobs->in);
			return NULL;
		}
		WRITELOG("search [%s] success!", pjobs->in);
	}

	if(pjobs->out[0] != '\0')
	{
		ret = hash_search(pboss->pipelines, pjobs->out, strlen(pjobs->out), &(void*)out);
		if(ret != 0)
		{
			WRITELOG("search [%s], pipeline failed!", pjobs->out);
			return NULL;
		}
		WRITELOG("search [%s] success", pjobs->out);
	}

	pid = fork();	
	if(pid < 0)
	{
		WRITELOG("fork failed!");
		return NULL;
	}

	if(pid == 0)
	{
		if(pjobs->work != NULL)
			pjobs->work((void*)in, (void*)out, NULL);
		exit(0);
	} else {
		ret = hash_insert(pboss->id_list, pjobs->job_name, strlen(pjobs->job_name), (void*)pid);	
		if(ret < 0)
		{
			WRITELOG("insert job pid %d failed!\n", pid);	
			return NULL;
		}
	}
	
	return NULL;
}
/**
 * \brief test the alloc
 */
static void* pipe_test(hash_node_st *node, void *cont)
{
	int i = 0;	
	ct_pipeline_st *ppipe = (ct_pipeline_st*)(node->data);
	chunk_ring_st *pring = ppipe->pipe;
	
	for(i = 0 ; i < pring->prod.size-1; ++i)
	{
		pring->buffer[i] = i%26 + 'a';	
	}
	pring->buffer[i] = '\0';

	WRITELOG("fulfil the ring : %s", pring->buffer);

	return 0;
}

ct_boss_st *angla_boss_init(const char *name)
{
	ct_boss_st *pboss = NULL;	

	pboss = (ct_boss_st *)calloc(1, sizeof(ct_boss_st));
	if(pboss == NULL)
	{
		WRITELOG("calloc boss failed!");	
		return NULL;
	}

	WRITELOG("init boss: %s", name);

	snprintf(pboss->boss_name, IDENTITY_LEN, "%s", name);

	pboss->pipelines = hash_init(NULL, NULL);
	if(pboss->pipelines == NULL)
	{
		WRITELOG("calloc pipelines jobs failed!");	
		return NULL;
	}

	pboss->jobs = hash_init(NULL, NULL);
	if(pboss->jobs == NULL)
	{
		WRITELOG("calloc jobs hash failed!");
		return NULL;
	}

	pboss->id_list = hash_init(NULL, NULL);
	if(pboss->id_list == NULL)
	{
		WRITELOG("calloc id_list failed!");	
		return NULL;
	}

	return pboss;
}

ct_pipeline_st *angla_pipeline_init(const char *name, unsigned int pipe_len)
{
	ct_pipeline_st *ppipe = NULL;	

	ppipe = (ct_pipeline_st *)calloc(1, sizeof(ct_pipeline_st));
	if(ppipe == NULL)
	{
		WRITELOG("calloc pipe line failed!");	
		return NULL;	
	}

	WRITELOG("init pipe_line: %s, pipe_len: %d", name, pipe_len);
	
	snprintf(ppipe->pipe_name, IDENTITY_LEN, "%s", name);

	ppipe->pipe_len = pipe_len;

	return ppipe;
}

ct_job_st *angla_job_init(const char *name,
						  const char *in,
						  const char *out,
						  int worker_num,
						  work_func_st work,
						  void *userdata)
{
	ct_job_st *pjobs = NULL;	

	pjobs = (ct_job_st*) calloc(1, sizeof(ct_job_st));
	if(pjobs == NULL)
	{
		WRITELOG("calloc jobs failed!");
		return NULL;
	}
	
	WRITELOG("init job: %s, worker_num: %d", name, worker_num);

	snprintf(pjobs->job_name, IDENTITY_LEN, "%s", name);
	snprintf(pjobs->in, IDENTITY_LEN, "%s", in);
	snprintf(pjobs->out, IDENTITY_LEN, "%s", out);

	pjobs->worker_num = worker_num;
	pjobs->work = work;
	pjobs->userdata = userdata;
	
	return pjobs;
}

int angla_add_job(ct_boss_st *pboss, ct_job_st *pjob)
{
	ASSERT(pboss != NULL && pjob != NULL, -1);
	
	int ret = 0;

	ret = hash_insert(pboss->jobs, 
					  pjob->job_name,
					  strlen(pjob->job_name),
					  (void*)pjob);
	if(ret != 0)
	{
		WRITELOG("insert new job failed!");
		return -1;
	}

	WRITELOG("add job: %s", pjob->job_name);

	return 0;
}

int angla_add_pipeline(ct_boss_st *pboss,
					   ct_pipeline_st *ppipe)
{
	ASSERT(pboss != NULL && ppipe != NULL, -1);

	int ret = 0;

	ret = hash_insert(pboss->pipelines, 
					  ppipe->pipe_name,
					  strlen(ppipe->pipe_name),
					  (void*)ppipe);
	if(ret != 0)
	{
		WRITELOG("insert new pipeline failed!");
		return -1;
	}

	WRITELOG("add pipeline: %s", ppipe->pipe_name);

	return 0;
}

int angla_boss_run(ct_boss_st *pboss)
{
	ASSERT(pboss != NULL, -1);		

	int ret = 0;
	pipe_count_st count;
	memset(&count, 0, sizeof(count));
	
	hash_walk(pboss->pipelines, pipe_len_walk, (void*)&count);	
	
	WRITELOG("current pipe line len: %d", count.total_len);

	if(count.total_len > 0)
	{
		pboss->share_mm_len = count.total_len;
		pboss->share_mm = (char*)calloc(1, count.total_len);
		if(pboss->share_mm == NULL)
		{
			WRITELOG("calloc share mem failed!");
			return -1;
		}

		hash_walk(pboss->pipelines, pipe_alloc_walk, pboss->share_mm);	
#ifdef CTDEBUG 
		hash_walk(pboss->pipelines, pipe_test, NULL);
#endif
	}

	if(pboss->share_mm != NULL)	
	{
		hash_walk(pboss->jobs, hire_worker, pboss);	
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int ret = 0;
	ct_boss_st *pboss = angla_boss_init("code tracer");		

	ct_pipeline_st *pipeA = angla_pipeline_init("pipeA", 1024);	
	ct_pipeline_st *pipeB = angla_pipeline_init("pipeB", 1024);
	ct_pipeline_st *pipeC = angla_pipeline_init("pipeC", 1024);

	ct_job_st *jobA = angla_job_init("jobA", NULL, "pipeA", 4, NULL, NULL);
	ct_job_st *jobB = angla_job_init("jobB", "pipeA", "pipeC", 4, NULL, NULL);
	ct_job_st *jobC = angla_job_init("jobC", "pipeC", NULL, 2, NULL, NULL);
	
	ret = angla_add_job(pboss, jobA);	
	ret = angla_add_job(pboss, jobB);	
	ret = angla_add_job(pboss, jobC);	

	ret = angla_add_pipeline(pboss, pipeA);
	ret = angla_add_pipeline(pboss, pipeB);
	ret = angla_add_pipeline(pboss, pipeC);

	angla_boss_run(pboss);
	
	return 0;
}



