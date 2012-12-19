/**
 * @file  xheap.h
 * @author  wzj
 * @brief copy? from sangfor, writen by wxc
 * @version 1.0
 * @note simple heap, you can use it as a little root/big root heap. 
 * @date: 2012年08月01日星期三22:27:56
 * 
 */ 
#ifndef _X_HEAP_H__
#define _X_HEAP_H__

/**
 * self define compare function, if you want to get a big heap, 
 * return the '>' result. Otherwise, it turns to a little heap. 
 */
typedef int (*cmp_func_t)(void*, void*);

/**
 * The main struct, heap struct.
 *
 */
typedef struct _xheap_st{
	void** base;				/**< heap array. store all element. */
	unsigned int heap_size;		/**< current heap size. */
	unsigned int nbase;			/**< total element. */

	cmp_func_t cmp;				/**< compare func, just like the qsort. */
}xheap_st;

/**
 * \brief create function, get a heap, big/small root, 
 * depends on you. default is the small one.
 * \param cmpfunc if the bigger one return 1, it is the big heap. 
 * default is the small heap.
 * \param heap_size the heap length.
 * \return NULL failed.
 * \return !NULL success you get a heap.
 */
xheap_st *heap_create(cmp_func_t cmpfunc, unsigned int heap_size);

/**
 * \brief destroy the heap.
 * \param pheap the sorrow heap you'll release.
 */
void heap_destroy(xheap_st *pheap);

/**
 * \brief push a value into the heap.
 * \param pheap main heap struct
 * \param data the target value
 * \return 0 success
 * \return !0 failed
 */
int heap_push(xheap_st *pheap, void *data);

/**
 * \brief get the max/min value
 * \param pheap main heap struct
 * \param [out] data if you pop one, it's value stored here
 * \return 0 success.
 * \return !0 failed
 */
int heap_pop(xheap_st *pheap, void **data);

#endif

