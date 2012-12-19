/**
 * \file chunk_ring.c
 * \author  wzj
 * \brief 多读者写者环形缓冲区。
 * \version 
 * \note 隐式队列的思想，所有进程都在缓冲区内排队
 * 按照顺序读写。`
 * \date: 2012年08月11日星期六00:28:13
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>

#include "chunk_ring.h"
#include "Jlog.h"

#define IS2UP(x)	((x)&((x)-1))

inline int cas(volatile unsigned int *mem, unsigned int new_val, unsigned int old_val)
{
	//__typeof (*mem) ret = 0;
	char ret = 0;
	/* cmpxchgl 默认第二个操作数与eax比较，相等，则源赋值到目的*/
	__asm __volatile (
			"lock; cmpxchgl %2, %1\n\t"	
			"sete %0"
			//:"=a" (ret),
			:"=r" (ret),
			 "=m" (*mem)
			:"r" (new_val),
			 "m" (*mem), 
			 "a" (old_val)
			);
	return (int)ret;
}

chunk_ring_st *chunk_ring_init(char *name, char *buffer, unsigned int size)
{
	if(IS2UP(size))	
		return NULL;

	chunk_ring_st *pring = (chunk_ring_st*)buffer;

	snprintf(pring->chunk_name, CHUNK_NAME_LEN, "%s", name);
	
	pring->prod.size = pring->cons.size = size;	
	pring->prod.mask = pring->cons.mask = size - 1;
	pring->prod.head = pring->cons.head = 0;
	pring->prod.tail = pring->cons.tail = 0;

	return pring;
}

int chunk_ring_enqueue(chunk_ring_st *chunk, char *data, unsigned int len)
{
	unsigned int tail, head;	
	unsigned int new_tail, new_head;
	unsigned int cur_left, cur_pos, size, mask;
	int success = 0;

	size = chunk->prod.size;
	mask = chunk->prod.mask;
	do{
		tail = chunk->cons.tail;
		head = chunk->prod.head;
		cur_left = tail - head + mask;	/* 有问题，这个可能是错的,利用2的幂的数的特殊性质，得到余数 */
		
		if(cur_left < len + sizeof(len))
			return -1;
		/* 溢出也不要紧，因为head与tail相差不会超过一个size */
		new_head = head + len + sizeof(len);
		WRITELOG("write head[%d]\n", new_head);
		
		success = cas(&(chunk->prod.head), new_head, head);
#if 0
		/* 需要原子锁 */
		if(head == chunk->prod.head)
		{	/* 证明目前为止，校验的缓冲区是可用的，然后分配掉 */
			chunk->prod.head = new_head;
			success = 1;
		}
#endif
	}while(!success);

	cur_pos = head & mask;	
	if(size - cur_pos > sizeof(len))
	{
		memcpy(chunk->buffer + cur_pos, (char*)&len, sizeof(len));
	} else {
		size_t l = size - cur_pos;/* cur_pos 一定指向可写的单元 */	
		memcpy(chunk->buffer + cur_pos, &len, l);	
		memcpy(chunk->buffer, (char*)(&len) + l, sizeof(len) - l);	
	}
	/* 神奇的mask */
	cur_pos = (cur_pos + sizeof(len)) & mask;
	if(size - cur_pos > len)
	{
		memcpy(chunk->buffer + cur_pos, data, len);
	} else {
		size_t l = size - cur_pos;	
		memcpy(chunk->buffer + cur_pos, data, l);
		memcpy(chunk->buffer, data + l, len - l);
	}
	/* 等待其他人完成插入 */
	while(chunk->prod.tail != head)
		sched_yield();
	
	chunk->prod.tail = new_head;

	return 0;
}

int chunk_ring_dequeue(chunk_ring_st *chunk, char **data, unsigned int *len)
{
	unsigned int head, tail;	
	unsigned int new_head, new_tail;
	unsigned int size, mask, cur_pos, cur_left, buf_len;
	int success = 0;
	
	size = chunk->cons.size;
	mask = chunk->cons.mask;

	do{
		head = chunk->cons.head;	
		tail = chunk->prod.tail;
		cur_left = tail - head;	/* 不需要加mask，因为可以保证tail始终在head之前的即使回绕了，也没有问题 */

		WRITELOG("%u", cur_left);
		if(cur_left < sizeof(unsigned int))
			return -1;
		
		if(((head + sizeof(unsigned int))&mask) < size)
		{
			memcpy((char*)&buf_len, chunk->buffer + (head & mask), sizeof(unsigned int));
		} else {
			size_t l = (size - head & mask); 
			memcpy((char*)&buf_len, chunk->buffer + (head & mask), l);
			memcpy((char*)&buf_len + l, chunk->buffer, sizeof(unsigned int) - l);
		}

		new_head = head + buf_len + sizeof(unsigned int) ; 
		success = cas(&(chunk->cons.head), new_head, head);
#if 0		
		new_head = head + buf_len + sizeof(unsigned int) ; 
		if(head == chunk->cons.head)	
		{
			chunk->cons.head = new_head;	
			success = 1;
		}
#endif
	}while(!success);
	
	*data = (char*) malloc(buf_len * sizeof(char));
	if(*data == NULL)
		return -1;
	
	cur_pos = (head + sizeof(unsigned int)) & mask;
	if(size - cur_pos > buf_len)
	{
		memcpy(*data, chunk->buffer + cur_pos, buf_len );
	} else {
		size_t l = size - cur_pos;
		memcpy(*data, chunk->buffer + cur_pos, l);
		memcpy(*data+l, chunk->buffer, buf_len - l);
	}

	*len = buf_len;

	while(head != chunk->cons.tail)
		sched_yield();
	
	chunk->cons.tail = new_head;
	return 0;
}
#if RING_TEST
int main()
{
	int total_size = sizeof(chunk_ring_st) + 64;
	char * buf = NULL;
	
	buf = (char*) calloc(1, total_size);
	if(buf == NULL)
	{
		WRITELOG("calloc failed!");
		return -1;
	}
	
	chunk_ring_st *pring = chunk_ring_init("test_ring", buf, 64);
	if(pring == NULL)
	{
		WRITELOG("init chunk ring failed!");
		return -1;
	}

	WRITELOG("%d\n", pring->prod.mask);
	int i = 0;
	
	while(1)
	{
		char *input	= "123abc";
		char *output = NULL;
		int out_len = 0;

		if(-1 == chunk_ring_enqueue(pring, input, strlen(input) + 1))
		{
			WRITELOG("enqueue failed!");
			return 0;
		}
		if(-1 == chunk_ring_dequeue(pring, &output, &out_len))
		{
			WRITELOG("dequeue failed!");
			return 0;
		}

		i++;	
		WRITELOG("dequeue: [%s][%d]", output, i);
		free(output); 
		output = NULL;
	}
	
	return 0;
}
#endif
