/**
 * \file ctslab.h
 * \author  wzj
 * \brief 
 	a slab just like the nginx slab.
 * \version 
 * \note  
 * \date: 2012年11月02日星期五23:15:54
 * 
 * discript your detail info.
 */ 

#ifndef _CT_SLAB_
#define _CT_SLAB_

#define SYSTEM_PAGE_SIZE		(4*1024)
#define SYSTEM_PAGE_OFFSET		(12)
#define MAX_SLAB_OFFSET			(11)		/* half page */
#define MID_SLAB_OFFSET			(7)			/* bit map split */
#define MIN_SLAB_OFFSET			(3)			/* 8 bytes */
#define BIT_MASK				(0xFF)
#define SIZEOFBITS(value)		((sizeof(value) * 8))	/* ... */

#define MEM_ALAIGN(buffer)	((char*)(((unsigned int)buffer+ (1 << SYSTEM_PAGE_OFFSET)-1) & ~((1 << SYSTEM_PAGE_OFFSET)-1)))

enum _SLAB_OFFSET_TYPE{
	SLAB_TYPE_SMALL = 0,
	SLAB_TYPE_MIDDLE,
	SLAB_TYPE_LARGE
};

typedef struct _ct_page_mgr_st ct_page_mgr_st;
typedef struct _ct_slot_head_st ct_slot_head_st;
typedef struct _ct_slab_head_st ct_slab_head_st;
typedef unsigned int uint;

/**
 * the page head, manage the pages.
 */
struct _ct_page_mgr_st{
	ct_slot_head_st *prv;
	ct_page_mgr_st *next;

	unsigned int slab_offset;
};

/**
 * the slab list manager
 */
struct _ct_slot_head_st{
	ct_page_mgr_st *free_slab_list;
	ct_slot_head_st *next;	

	unsigned int slab_offset;
};

/**
 * slab head which is the manager
 */
struct _ct_slab_head_st{
	char *begin;
	char *end;

	ct_slot_head_st *slots;
	unsigned int nslots;

	ct_page_mgr_st *pages;
	ct_page_mgr_st *free_page_list;
	unsigned int used_pages;
	unsigned int npages;

	unsigned int total_size;
};

#endif


