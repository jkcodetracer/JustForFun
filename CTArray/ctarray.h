/**
 * \file ctarray.h
 * \author  wzj
 * \brief 
 	simple array...
 * \version 
 * \note  
 * \date: 2012年11月10日星期六06:58:48
 * how to
 * 1. get a n * size room(with the ct_array_push/ct_array_push_n)
 * 2. the you can use the n rooms free.
 */ 

#ifndef __CTARRAY_H_
#define __CTARRAY_H_

/* array main struct */
typedef struct _ct_array_st{
	void 			*elts;			/* point to the array head */
	unsigned int 	nelts;			/* current array length */
	unsigned int 	size;			/* a single room size */
	unsigned int 	nalloc;			/* the array total memory */
	
	void			*allocator;		/* the memory allocator */
}ct_array_st;

/**
 * \brief the array createor
 * \param size 		a single room length
 * \param nalloc 	the array's total memory len
 * \param allocator the self defined memory allocator, if NULL, use the malloc 
 * \return  success return the ct_array_st
 *			failed  return NULL
 */
ct_array_st *ct_array_creat(unsigned int size, unsigned int nalloc, void *allocator);

void ct_array_destroy(ct_array_st *parray);

void *ct_array_push(ct_array_st *parray);

void *ct_array_push_n(ct_array_st *parray, unsigned int len);

#endif
