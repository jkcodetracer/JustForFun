/**
 * \file pipeline.h
 * \author  wzj
 * \brief for multi thread and 并行计算
 * \version 1.0 
 * \note  
 * \date: 2012年08月23日星期四21:06:25
 */ 

#ifndef _JUSTFORFUN_CTPIPELINE_
#define _JUSTFORFUN_CTPIPELINE_

#include "../XHASH/xhash.h"
#include "../ChunkRing/chunk_ring.h"
/* 名字长度 */
#define IDENTITY_LEN	(96)

typedef void (*work_func_st)(void* userdata);

typedef struct _ct_pipeline_st{
	char pipe_name[IDENTITY_LEN];

	unsigned int pipe_len;
	chunk_ring_st *pipe;	
}ct_pipeline_st;

typedef struct _ct_job_st{ 
	char job_name[IDENTITY_LEN];

	char in[IDENTITY_LEN];
	char out[IDENTITY_LEN];

	unsigned int worker_num;
	work_func_st work;
	void * userdata;	
}ct_job_st;

typedef struct _ct_boss_st{
	char boss_name[IDENTITY_LEN];	

	hash_table_st *pipelines;
	hash_table_st *jobs;

	char *share_mm;	
	unsigned int share_mm_len;

	hash_table_st *id_list;
}ct_boss_st;

/**
 * \brief init the boss
 * \note take care of the hash has alloced, you should release them. 
 */
ct_boss_st *angla_boss_init(const char *name);

/**
 * \brief init the pipeline
 */
ct_pipeline_st *angla_pipeline_init(const char *name, unsigned int pipe_len);

/**
 * \brief init the jobs
 */
ct_job_st *angla_job_init (const char *name, 
						   const char *in, 
						   const char *out,
						   int worker_num,
						   work_func_st work,
						   void *userdata);
/**
 * \brief add jobs to the boss
 */
int angla_add_job(ct_boss_st *pboss, 
				  ct_job_st *pjob);
/**
 * \brief add new pipeline
 */
int angla_add_pipeline(ct_boss_st *pboss,
					   ct_pipeline_st *ppipe);
/** 
 * \brief let go ! begin process the data
 */
int angla_boss_run(ct_boss_st *pboss);

/** 
 * \brief stop all!
 */
int angla_boss_stop();

#endif
