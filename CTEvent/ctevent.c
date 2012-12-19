/**
 * \file ctevent.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年11月13日星期二23:04:33
 * 
 * discript your detail info.
 */ 
#include <Jlog.h>

#include "ctevent.h"

static ct_listener_st *ct_listener_init(int event_type, 
										event_handler *phandler)
{
	ct_listener_st *plistener = NULL;

	plistener = (ct_listener_st *) calloc(1, sizeof(ct_listener_st));
	if(plistener == NULL)
	{
		dblog("malloc event listener failed!");
		return NULL;
	}

	plistener->ev_handler = phandler;
	ct_queue_init(&plistener->link);
	
	return plistener;
}


int ct_listener_add(ct_event_ctrl_st *pctrler, 
					int event_type,
					event_handler *phandler)
{
	ASSERT(pctrler != NULL && phandler != NULL, -1);
	
	ct_listener_st *plistener = NULL;

	plistener = ct_listener_init(event_type, phandler);
	if(plistener == NULL)
	{
		dblog("init listener failed!");
		return -1;
	}

	ct_queue_insert_tail(&pctrler->listener_set[event_type].link,
						&plistener->link);	
	
	return 0;
}

ct_event_ctrl_st *ct_event_ctrler_init(void)
{
	ct_event_ctrl_st *pctrler = NULL;

	pctrler = (ct_event_ctrl_st *)calloc(1, sizeof(*pctrler));
	if(pctrler == NULL)
	{
		dblog("malloc event ctrler failed!");
		return NULL;
	}

	return pctrler;
}

int ct_event_emit(ct_event_node_st *plist, ct_evnet_st *pevent)
{
	ASSERT(plist != NULL && pevent != NULL, -1);	
	ct_event_node_st *new_node = NULL;

	new_node = (ct_event_node_st *)calloc(1, sizeof(*new_node));
	if(new_node == NULL)
	{
		dblog("new_node malloc failed!");
		return -1;
	}

	ct_queue_init(&new_node->link);
	new_node->ev = pevent;

	ct_queue_insert_tail(&plist->link,
						&new_node->link);
	
	return 0;
}

int ct_event_processor(ct_event_ctrl_st *pctrlor,
						ct_event_node_st *plist)
{
	ASSERT(pctrlor != NULL, -1);

	ct_event_node_st 	*pnode 		= NULL;
	ct_listener_st 		*plistener 	= NULL;
	ct_listener_st		*pdealer	= NULL;
	ct_queue_st 		*plink 		= NULL;
	int 				event_type 	= 0;

	plink = &plist->link;

	while(1)
	{
		if(ct_queue_is_empty(plink))
		{
			dblog("the event list cleaned!");
			break;
		}
		
		pnode 		= ct_queue_data(plink, ct_event_node_st, link);
		event_type 	= pnode->ev->event_type;
		plistener	= &pctrlor->[event_type];
		pdealer 	= ct_queue_next(plistener);
		
		while(pdealer != plistener)
		{
			pdealer->hander(pnode->ev, NULL);						
			pdealer = ct_queue_next(pdealer);
		}

		ct_queue_remove(plink);
		/* TODO free pnode! */

		plink = ct_queue_next(&plist->link);
	}
	
	return 0;
}


