/**
 * \file ctlistener.h
 * \author  wzj
 * \brief 
 	event handler...
 * \version 
 * \note  
 * \date: 2012年11月13日星期二23:08:28
 * 
 * discript your detail info.
 */ 
#ifndef _CT_LISTENER_H_
#define _CT_LISTENER_H_

typedef struct _ct_listener_st{
	
	void 		 *private_data;		/*<< private date  */
	event_hander *phandler;			/*<< event handler */
}ct_listener_st;

#endif

