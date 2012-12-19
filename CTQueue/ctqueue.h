/**
 * \file ctqueue.h
 * \author  wzj
 * \brief 
 	simple list(queue) opr
 * \version 
 * \note  
 * \date: 2012年11月14日星期三07:20:11
 * 
 */ 
#ifndef _CT_QUEUE_H_
#define _CT_QUEUE_H_

#include <stddef.h>

typedef struct _ct_queue_st ct_queue_st;

struct _ct_queue_st{
	ct_queue_st 	*prev;
	ct_queue_st		*next;
};
/* init queue */
#define ct_queue_init(h)				\
	(h)->prev = (h);					\
	(h)->next = (h)
/* is empty */
#define ct_queue_empty(h)				\
	((h) == (h)->prev)			

#define ct_queue_insert_head(h, x)		\
	(x)->next = (h)->next;				\
	(x)->next->prev = x;				\
	(x)->prev = h;						\
	(h)->next = x

#define ct_queue_insert_tail(h, x)		\
	(x)->prev = (h)->prev;				\
	(x)->prev->next = x;				\
	(x)->next = h;						\
	(h)->prev = x

#define ct_queue_head(h)				\
	(h)->next	

#define ct_queue_tail(h)				\
	(h)->prev

#define ct_queue_next(n)				\
	(n)->next

#define ct_queue_prev(n)				\
	(n)->prev

#define ct_queue_remove(x)				\
	(x)->next->prev = (x)->prev;		\
	(x)->prev->next = (x)->next			
/* 为什么会包含头部? 还是根本就不该有头部 */
#define ct_queue_split(h, q, n)			\
	(n)->prev = (h)->prev;				\
	(n)->prev->next = n;				\
	(h)->prev = (q)->prev;				\
	(h)->prev->next = h;				\
	(n)->next = q;						\
	(n)->next->prev = n

#define ct_queue_split1(h, q, n)        \
	(n)->prev = (h)->prev;              \
   	(n)->prev->next = n;                \
   	(n)->next = q;                      \
	(h)->prev = (q)->prev;              \
	(h)->prev->next = h;                \
	(q)->prev = n
/* 合并两个链表,丢掉头部x */
#define ct_queue_add(h, x)				\
	(h)->prev->next = (x)->next;		\
	(x)->next->prev = (h)->prev;		\
	(h)->prev = (x)->prev;				\
	(h)->prev->next = h

#define ct_queue_is_empty(h)			\
	{((h)->prev == (h)->next)?1:0}

#define ct_queue_data(q, type, link)	\
	(type*)((char*)q - offsetof(type, link))

#endif

