/**
 * \file ctevent.h
 * \author  wzj
 * \brief 
 	event list!
 * \version 
 * \note  
 * \date: 2012年11月13日星期二23:04:41
 * 
 * discript your detail info.
 */ 
#ifndef _CT_EVENT_H_
#define _CT_EVENT_H_

#include "../XHASH/xhash.h"
#include "../CTQueue/ctqueue.h"

#define MAX_EVENT_TYPE			(32)	/**< 偷个懒，目前只支持32类不同的事件 */
#define MAX_SIGNLE_LISTENER		(32)	/**< 每种类型最多32个监听者 */	

typedef struct _ct_listener_st 		ct_listener_st;			/**< 监听者回调 */
typedef struct _ct_event_ctrl_st 	ct_event_ctrl_st;		/**< 事件机制的核心，回调反射机制 */
typedef struct _ct_event_node_st 	ct_event_node_st;		/**< 事件节点 */
typedef struct _ct_event_st 		ct_event_st;			/**< 事件,可以自由扩展 */

//typedef hash_table_st				ct_event_list;			/**< 事件集合， 里面放满了事件节点 */

int (*event_handler)(ct_event_st *pevent, void *private_data);
/* 事件结构体 */
struct _ct_event_st{
	int 	event_type;			/**< 事件类型 */
	char 	event[1];			/**< 事件内容, 可以自由扩展任何类型 */
};

/* 事件节点 */
struct _ct_event_node_st{
	ct_queue_st	link;			/**< 以链表的形式存储  */
	ct_event_st *ev;			/**< 需要处理的事件 */
};

/* 事件处理结构, 监听者 */
struct _ct_listener_st{
	ct_queue_st		link;

	int 			event_type;	/**< 事件类型 */
	event_handler	ev_handler; /**< 监听者的回调 */
};
/* 事件机制的核心 */
struct _ct_event_ctrl_st{
	ct_listener_st listener_set[MAX_EVENT_TYPE];
};

/**
 * \brief event listener init
 */
static ct_listener_st *ct_listener_init(int event_type, event_hander *phandler);

/**
 * \brief event listener add
 */
int ct_listener_add(ct_event_ctrl_st *pctrler, int event_type, event_handler *phandler);

/**
 * \brief init event ctrler
 */
ct_event_ctrl_st *ct_event_ctrler_init(void);

/**
 * \brief add new event
 */
int ct_event_emit(ct_event_node_st *plist, ct_event_st *pevent);

/**
 * \brief event loop
 */
int ct_event_loop(); 

/**
 * \brief event processor
 */
int ct_event_processor(ct_event_ctrl_st *pctrlor, ct_event_node_st *plist);


#endif





