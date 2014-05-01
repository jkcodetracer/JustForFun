/**
 * \file pap_list.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年06月10日星期一11:23:11
 * 
 * discript your detail info.
 */ 
#ifndef _PAP_LIST_H_WZJ
#define _PAP_LIST_H_WZJ

typedef struct _list_st{
	struct _list_st *prev;
	struct _list_st *next;
}list_st;

typedef void list_cb(list_st *, void *arg);

#define LIST_NEXT(p, type, item) p->next?GET_ENTRY(p->next, type, item):NULL
#define LIST_PREV(p, type, item) p->prev?GET_ENTRY(p->prev, type, item):NULL

#define LIST_INIT(p)				(p.prev = p.next = &p)
#define LIST_IS_EMPTY(head)  		(head.prev == head.next?1:0)	

#define LIST_ADD_FRONT(head, newtail) do {				\
							newtail.next = &head;		\
							newtail.prev = head.prev;	\
							head.prev->next = &newtail;	\
							head.prev = &newtail;		\
						}while(0)

#define LIST_ADD_BEHIND(head, newhead) do {				\
							newhead.next = head.next;	\
							newhead.prev = &head;		\
							head.next->prev = &newhead;	\
							head.next = &newhead;		\
						}while(0)

#define LIST_DEL_FRONT(head, pfront) 	do{					\
							pfront = head.prev;				\
							if (head.prev== NULL || 		\
							   LIST_IS_EMPTY(head))			\
							{	pfront = NULL;				\
							   	break;		}				\
							pfront->prev->next = &head;		\
							head.prev = pfront->prev;		\
							pfront->prev =					\
							pfront->next = pfront;			\
						}while(0)

#define LIST_DEL_BEHIND(head, pbehind)	do{					\
							pbehind = head.next;			\
							if (pbehind == NULL ||			\
								LIST_IS_EMPTY(head))		\
							{	pbehind = NULL;				\
								break;		}				\
							pbehind->next->prev = &head;	\
							head.next = pbehind->next;		\
							pbehind->prev = 				\
							pbehind->next = pbehind;		\
						}while(0)

#define LIST_TRAVERSE(head, list_cb, cbarg)	do{				\
							list_st *pnode = head.next;		\
							for (;pnode != &head; 			\
								 pnode = pnode->next		\
								)							\
								list_cb(pnode, cbarg);		\
						}while(0)

#define LIST_ADD_HEAD(head, newhead) LIST_ADD_BEHIND(head, newhead)
#define LIST_ADD_TAIL(head, newtail) LIST_ADD_FRONT(head, newtail)
#define LIST_DEL_HEAD(head, pdelhead) LIST_DEL_BEHIND(head, pdelhead)
#define LIST_DEL_TAIL(head, pdeltail) LIST_DEL_FRONT(head, pdeltail)

#endif


