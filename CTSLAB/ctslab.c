/**
 * \file ctslab.c
 * \author  wzj
 * \brief 
 	a simple slab just like the nginx
 * \version 
 * \note  
 * \date: 2012年11月02日星期五23:45:03
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <Jlog.h>

#include "ctslab.h"

/**
 * \brief init the alloced buffer as a slab
 * \note input a valid buffer!
 */
ct_slab_head_st *ct_slab_init(char *buffer, unsigned int buffer_size)
{
	if(buffer == NULL || buffer_size <= SYSTEM_PAGE_SIZE )	
	{
		dblog("invalid input! the buffer must be valid!");
		return NULL;
	}
	ct_slab_head_st    *phead   = NULL;
	unsigned int 		tmplen  = buffer_size;
	char 			   *pbuffer = NULL;
	int					i 		= 0;

	memset(buffer, 0, sizeof(char)*buffer_size);
	
	phead = (ct_slab_head_st *)buffer;
	pbuffer = buffer + sizeof(*phead);
	tmplen -= sizeof(*phead);
	
	phead->nslots = MAX_SLAB_OFFSET - MIN_SLAB_OFFSET + 1;
	phead->slots = (ct_slot_head_st*)pbuffer;

	for( i = 0; i < phead->nslots; i++)
	{
		ct_slot_head_st *pslot = phead->slots + sizeof(*pslot)*i;	
		pslot->slab_offset = MIN_SLAB_OFFSET + i;
	}

	pbuffer = pbuffer + sizeof(*(phead->slots))*phead->nslots;	
	tmplen -= sizeof(*(phead->slots))*phead->nslots;

	phead->pages = (ct_page_mgr_st* )pbuffer;
	phead->npages = tmplen/(sizeof(ct_page_mgr_st) + SYSTEM_PAGE_SIZE);
	
	phead->free_page_list = phead->pages;
	for(i = 0; i < phead->npages - 1; i++)
		phead->pages[i].next = &phead->pages[i+1];

	pbuffer += sizeof(ct_page_mgr_st) * phead->npages;
	//pbuffer = (char*)(((unsigned int)pbuffer + (1 << SYSTEM_PAGE_OFFSET) - 1) & 
	//					~((1 << SYSTEM_PAGE_OFFSET)-1));	/* do alaign */
	
	pbuffer = MEM_ALAIGN(pbuffer);
	
	phead->used_pages = 0;		
	phead->begin = pbuffer;	
	phead->end = buffer + buffer_size;
	phead->total_size = buffer_size;

	return phead;
}
/*
int ct_slab_alloc_slab(ct_slab_head_st *phead, uint offset)
{
	ASSERT(phead != NULL && offset > 0, -1);
	
}
*/

void *ct_slab_alloc(ct_slab_head_st *phead, unsigned int nsize)
{
	ASSERT(phead != NULL, NULL);	
	
	ct_slot_head_st *pslots = NULL;
	ct_page_mgr_st *ppagemgr = NULL;
	unsigned int offset = 1;
	char *ppage = NULL;
	char *alloced = NULL;
	char *mask = NULL;
	int blockpos = -1;
	int nblocks = 0;
	int nbytes = 0;
	int nbits = 0;
	int i = 0, j = 0;

	/* get the offset, the min is 3, alaign to the 8byte */
	uint tmpsize = nsize;
	for(; tmpsize >>= 1; offset++){;}
	if(offset < MIN_SLAB_OFFSET)
		offset = MIN_SLAB_OFFSET;

	if(offset > MAX_SLAB_OFFSET)
	{
		dblog("malloc [%d] failed, over rage!", nsize);
		return NULL;
	}
	/* small piece */
	if(offset < MID_SLAB_OFFSET)
	{
		pslots = &phead->slots[offset - MIN_SLAB_OFFSET];	
		if(pslots->free_slab_list == NULL)
		{
			if(phead->used_pages == phead->npages)
				return NULL;
			ppagemgr = &phead->pages[phead->used_pages++];
			ppagemgr->prv = pslots;
			ppagemgr->slab_offset = offset;
			ppagemgr->next = pslots->free_slab_list;

			pslots->free_slab_list = ppagemgr;

			ppage = phead->begin + (ppagemgr - phead->pages)*SYSTEM_PAGE_SIZE;
			/* 初始化位图*/
			mask = ppage;
			nblocks = 1 << (SYSTEM_PAGE_OFFSET - offset);
			nbytes = nblocks/8;
			for(i = 0; i < nbytes/8; i++)	
				mask[i] = BIT_MASK;

			nbits = nbytes%8;
			for(j = 0; j < nbits; j++)
				mask[i] |= (1 << j);

			dblog("ppage:[%08X] nblocks[%d], mask[%d]", 
					(uint)ppage, nblocks, (uint)mask);
		}
		ppagemgr = pslots->free_slab_list;
		ppage = phead->begin + (ppagemgr - phead->pages)*SYSTEM_PAGE_SIZE;	
		/* 遍历位图 */
		nblocks = 1 << (SYSTEM_PAGE_OFFSET - offset); 
		nbytes = (nblocks + sizeof(char)-1)/sizeof(char);	/* got 8 bits, reach the upline. */
		mask = ppage;
		dblog("nblocks[%d], nbytes[%d], mask[%08x]", nblocks, nbytes, (uint)mask);
		for(i = 0; i < nbytes; i++)		
		{
			if(mask[i] == BIT_MASK)
				continue;
			for(j=0; j < sizeof(char); j++)	
			{
				if(mask[i] & (1 << j))
					continue;
				blockpos = i * sizeof(char) + j;			
				mask[i] |= 1 << j;
				break;
			}
			if(blockpos >= 0)
				break;
		}

		if(i >= nbytes)
		{
			dblog("move the slab outof the queue.");	
			pslots->free_slab_list = ppagemgr->next;
			ppagemgr->next = NULL;
		}

		dblog("alloc ppage[%08x] slab[%d] blockpos[%d]", (uint)ppage, offset, blockpos);	
		if(blockpos >= 0)
		{
			alloced = ppage + blockpos * (1 << offset);	
		}
	}
	/* middle piece */
	if(offset == MID_SLAB_OFFSET)
	{
		pslots = &phead->slots[offset - MIN_SLAB_OFFSET]; 					
		if(pslots->free_slab_list == NULL)
		{
			if(phead->used_pages == phead->npages)	
				return NULL;
			ppagemgr = &phead->pages[phead->used_pages++];
			ppagemgr->prv = pslots;
			ppagemgr->slab_offset = offset;
			ppagemgr->next = pslots->free_slab_list;
			ppagemgr->prv = (ct_slot_head_st* )((uint)ppagemgr->prv | SLAB_TYPE_MIDDLE);

			pslots->free_slab_list = ppagemgr;
		}
		ppagemgr = pslots->free_slab_list;		
		ppage = phead->begin + (ppagemgr - phead->pages)*SYSTEM_PAGE_SIZE;

		for(i = 0; i < SIZEOFBITS(ppagemgr->slab_offset); i++)
		{
			if(!(ppagemgr->slab_offset & (1 << i)))	
			{
				blockpos = i;
				ppagemgr->slab_offset |= (1 << i);
				break;
			}
		}

		if(i >= SIZEOFBITS(ppagemgr->slab_offset))
		{
			dblog("alloc middle page failed!");
			return NULL;
		}
		
		if(ppagemgr->slab_offset == 0XFFFFFFFF)
		{
			pslots->free_slab_list = ppagemgr->next;		
			ppagemgr->next = NULL;
		}

		alloced = ppage + blockpos * (1 << offset);	
	}

	/* large piece */
	if(offset > MID_SLAB_OFFSET)
	{
		pslots = &phead->slots[offset - MIN_SLAB_OFFSET];		
		if(pslots->free_slab_list == NULL)
		{
			if(phead->used_pages == phead->npages)
				return NULL;
			ppagemgr = &phead->pages[phead->used_pages++];
			ppagemgr->prv = pslots;
			ppagemgr->slab_offset = offset;
			ppagemgr->next = pslots->free_slab_list;
			ppagemgr->prv = (ct_slot_head_st*)((uint)ppagemgr->prv | SLAB_TYPE_LARGE);

			pslots->free_slab_list = ppagemgr;
		}
		ppagemgr = pslots->free_slab_list;
		ppage = phead->begin + (ppagemgr - phead->pages)*SYSTEM_PAGE_SIZE;
		
		uint offset_mask = ppagemgr->slab_offset >> 16; /* the high store the offset */
		for(i = 0; i < SIZEOFBITS(short); i++)
		{
			if(!(offset_mask & (1 << i)))
			{
				blockpos = i;
				offset_mask |= (1 << i);
				ppagemgr->slab_offset |= offset_mask << SIZEOFBITS(short);
				break;
			}
		}

		if(i >= SIZEOFBITS(short))
		{
			dblog("alloc large type slab failed!");
			return NULL;
		}

		if(offset_mask == 0xFFFF)
		{
			pslots->free_slab_list = ppagemgr->next;	
			ppagemgr->next = NULL;
		}

		alloced = ppage + blockpos * (1 << offset);
	}

	return alloced;
}

int ct_slab_free(ct_slab_head_st *phead, char *slab)
{
	ASSERT(phead != NULL && slab != NULL, -1);	

	ct_page_mgr_st *ppagemgr = NULL;
	unsigned int offset = 0;
	unsigned int slab_type = 0;
	int npage = 0;
	int nslab = 0;

	npage = (((uint)slab & (~((1 << SYSTEM_PAGE_OFFSET) - 1))) - 
					(uint)phead->begin)/(SYSTEM_PAGE_SIZE);
	ppagemgr = phead->pages + npage;
	
	if(ppagemgr == NULL)
	{
		dblog("get curpage failed!");
		return -1;
	}

	slab_type = (uint)ppagemgr->prv & 0x11;
	
	switch(slab_type)
	{
		case SLAB_TYPE_SMALL:
		{
			char *mask = phead->begin; 	
			int i = 0, j = 0;

			offset = ppagemgr->slab_offset;
			nslab = ((uint)slab & ((1 << SYSTEM_PAGE_OFFSET)-1))/(1 << offset);
			i = nslab / 8;
			j = nslab % 8;
			mask[i] &= ~(1 << j);
			/* add to the free list */	
			ppagemgr->next = ppagemgr->prv->free_slab_list;
			ppagemgr->prv->free_slab_list = ppagemgr;	
			break;
		}

		case SLAB_TYPE_MIDDLE:
		{
			ct_slot_head_st *pslots = (ct_slot_head_st*)((uint)ppagemgr->prv & 0x100);		
			offset = MID_SLAB_OFFSET;
			nslab = ((uint)slab & ((1 << SYSTEM_PAGE_OFFSET)-1))/(1 << offset);
			ppagemgr->slab_offset &= ~(1 << nslab);
			ppagemgr->next = ppagemgr->prv->free_slab_list;
			pslots->free_slab_list = ppagemgr;

			break;
		}
		case SLAB_TYPE_LARGE:
		{
			ct_slot_head_st *pslots = (ct_slot_head_st*)((uint)ppagemgr->prv & 0x100);
			offset = ppagemgr->slab_offset & 0xFFFF;
			nslab = ((uint)slab & ((1 << SYSTEM_PAGE_OFFSET)-1))/(1 << offset);
			
			ppagemgr->slab_offset &= ~((1 << nslab) << 16);
			ppagemgr->next = ppagemgr->prv->free_slab_list;
			pslots->free_slab_list = ppagemgr;
			break;
		}
		default:
			break;
	}

	memset(slab, 0, 1<<offset);

	return 0;	
}

int main(int argc, char *argv[])
{
	ct_slab_head_st *slab = NULL;
	char *buffer = malloc(1024 * 1024);
	char *allocated = NULL;
	int i = 0;
	
	slab = ct_slab_init(buffer, 1024*1024);

	dblog("phead: [%08x]", (uint)slab);
	dblog("nslots:[%08x]", (uint)&slab->nslots);
	dblog("slots: [%08x]", (uint)slab->slots);
	dblog("pages: [%08x]", (uint)slab->pages);
	dblog("npages:[%08x]", (uint)&slab->npages);
	dblog("npages:[%d]",   (uint)slab->npages);
	dblog("begin: [%08x]", (uint)slab->begin);
	dblog("end: [%08x]",   (uint)slab->end);

	for(i = 0; i < 10; i++)
	{
		allocated = ct_slab_alloc(slab, i + 1000);	
		if(allocated == NULL)
			dblog("alloc failed!");
		else 
			dblog("alloc [%08x]", (uint)allocated);

//		ct_slab_free(slab, allocated);
	}	
	
	return 0;
}


