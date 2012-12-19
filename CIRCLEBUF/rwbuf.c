/*
 * @FileName: rwbuf.c
 * @Author: wzj
 * @Brief: 
 * 1.读写环形缓冲区，一直使用连续内存，仅有一次拷贝， 
 * 2.当缓冲区读写重合时，是满的状态 
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月21日星期六23:05:47
 * 
 */ 
#include <stdio.h>
#include <string.h>
#include "Jlog.h"

enum{
	CRW_ERR = -1,
	CRW_COMMON = 0,
	CRW_TAIL = 1,
	CRW_HEAD = 2,
};

typedef struct __rw_buf_t rw_buf_t;

struct __rw_buf_t{
	int size;		//缓冲区的大小
	char *buffer;	//缓冲区指针
	int w_index;	//可写段的下标
	int r_index;	//可读段的下标
	int end_index;	//中止标记，用于保证缓冲区一直是连续的
	int check_magic;	//校验单元，如果被踩坏了，需要做处理
};

/*
 * init ... 
 *
 *
 */
static int
rw_init(rw_buf_t *rw_buf, char *buffer, int size, int magic)
{
	rw_buf->size = size;
	rw_buf->buffer = buffer;
	rw_buf->w_index = 0;
	rw_buf->r_index = 0;
	rw_buf->end_index = 0;
	rw_buf->check_magic = magic;
}


/*
 * 最后一个参数，这里主要考虑一个问题，如果不能一次性写完，那么，后续为了维持buffer的线性
 * 就要写一个预期值进来，保证同一段数据分多次写，也能在一块线性地址上
 *
 */
static int
rw_write(rw_buf_t *rw_buf, char *w_buf, int w_buf_sz, int maxneed)
{
	int w_index = rw_buf->w_index;
	int r_index = rw_buf->r_index;
	int end_index = rw_buf->end_index;

	if(w_index >= r_index)
	{
		if(rw_buf->size - w_index > w_buf_sz &&
		   rw_buf->size - w_index > maxneed)	
		{
			memcpy(rw_buf->buffer + w_index, w_buf, w_buf_sz);	
			rw_buf->w_index += w_buf_sz;
			return CRW_COMMON;
		} else if(r_index > maxneed &&
				  r_index > w_buf_sz)
		{
			rw_buf->end_index = w_index;
			memcpy(rw_buf->buffer, w_buf, w_buf_sz);
			rw_buf->w_index = 0;
			return CRW_TAIL;
		} 
	} else if(r_index - w_index > w_buf_sz &&
			  r_index - w_index > maxneed)
	{
		memcpy(rw_buf->buffer + w_index, w_buf, w_buf_sz);			
		rw_buf->w_index += w_buf_sz;
		return CRW_HEAD;
	}

	return CRW_ERR;
}
/*
 *  read...
 *  return all bit
 *
 */
static int
rw_read(rw_buf_t *rw_buf, char **buf)
{
	int w_index = rw_buf->w_index;
	int r_index = rw_buf->r_index;
	int end_index = rw_buf->end_index;
	int r_size = 0;
	*buf = NULL;

	if(w_index != r_index)
	{
		if(r_index < w_index)	
		{
			r_size = w_index - r_index;	
		} else if(r_index < end_index)
		{
			r_size = end_index - r_index;
		} else if(r_index < rw_buf->size)
		{
			r_size = rw_buf->size - r_index;
		} else {
			r_index = 0;
			r_size = w_index - r_index;
		}
		*buf = rw_buf->buffer + r_index;	
	}

	return r_size;
}
/*
 *  read finish...
 *  调整下标
 *
 */
static void
rw_read_finish(rw_buf_t *rw_buf, int r_size)
{
	int w_index = rw_buf->w_index;
	int r_index = rw_buf->r_index;
	int end_index = rw_buf->end_index;

	if(w_index > r_index)
	{
		rw_buf->r_index += r_size;
	} else {
		if(end_index > 0 && 
			r_index + r_size < end_index)
		{
			rw_buf->r_index += r_size;
		} else if(end_index == 0 && 
				 r_index + r_size < rw_buf->size)
		{
			rw_buf->r_index += r_size;	
		} else {
			rw_buf->r_index = 0;
			rw_buf->end_index = 0;
		}
	}
}
/*
 *  快速恢复...
 *  
 *
 */
static void
rw_reserve_fast(rw_buf_t *rw_buf, int *tmpw, int *tmpr, int *tmpend)
{
	*tmpw = rw_buf->w_index; 
	*tmpr = rw_buf->r_index;
	*tmpend = rw_buf->end_index;

	if(*tmpr < *tmpw)
	{
		rw_buf->r_index = *tmpw;
	} else if(*tmpr > *tmpw)
	{
		rw_buf->r_index = *tmpend;
	}
}

#ifdef CTDEBUG

#include <stdio.h>
#include <stdlib.h>

#define TEST_BUFFER_SIZE	(64)
#define MAGIC_NUM		(234555)

int
try_fill_all(rw_buf_t *p_rw_buf, int part)
{
	ASSERT(p_rw_buf != NULL, 0);
	
	char test_string[TEST_BUFFER_SIZE] = {'\0'};
	int i = 0;
	int ret = 0;

	part = (part)?1:part;
	WRITELOG("write way:");
	for(i = 0; i < TEST_BUFFER_SIZE/part; i++)
	{
		snprintf(test_string, TEST_BUFFER_SIZE, "Insert%d...", i);
		ret = rw_write(p_rw_buf, (char*)test_string, strlen(test_string), strlen(test_string));	
		if (ret!=-1)
			WRITELOG("%d", ret);
	}

	return 0;
}

int 
try_read(rw_buf_t *p_rw_buf)
{
	char *pret = NULL;	
	int ret = rw_read(p_rw_buf, &pret);
	if(pret != NULL)
	{
		int j = 0;
		for(j = 0; j < ret; j++)
		{
			WRITELOG("%c", pret[j]);
		}
		WRITELOG("%d .. \n", ret);
		rw_read_finish(p_rw_buf, ret);
	} else {
		WRITELOG("read failed\n");
	}
}

void
deal_ret(int ret_num)
{
	switch(ret_num)
	{
		case CRW_ERR:
			WRITELOG("CRW_ERR..");
			break;
		case CRW_COMMON:
			WRITELOG("CRW_COMMON");
			break;
		case CRW_TAIL:
			WRITELOG("CRW_TAIL");
			break;
		case CRW_HEAD:
			WRITELOG("CRW_HEAD");
			break;
		default:
			WRITELOG("unknown");
			break;
	}
}

int
main()
{
	rw_buf_t test_buf = {0};	
	char test_string[TEST_BUFFER_SIZE] = {'\0'};
	int i = 0;
	int ret = 0;

	test_buf.buffer = (char*)malloc(TEST_BUFFER_SIZE);
	if(test_buf.buffer == NULL)
	{
		WRITELOG("malloc buf failed\n");		
		return -1;
	}
	//test init
	rw_init(&test_buf, test_buf.buffer, TEST_BUFFER_SIZE, MAGIC_NUM);

	//fullfill buffer
	try_fill_all(&test_buf, 1);

	//read 
	try_read(&test_buf);	

	try_fill_all(&test_buf, 15);
	try_read(&test_buf);
		
	try_fill_all(&test_buf, 30);
	try_read(&test_buf);
	try_read(&test_buf);

	try_fill_all(&test_buf, 32);
	try_read(&test_buf);
	try_read(&test_buf);
	
#if 0
	for(i = 0; i < TEST_BUFFER_SIZE; i++)
	{
		WRITELOG("test_buf[%d]: %c\n", i,test_buf.buffer[i]);
	}
#endif

	return 0;	
}

#endif
