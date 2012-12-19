/**
 * \file chunk_ring.h
 * \author  wzj
 * \brief  chunk ring... circle buffer, support multy user! 
 * many readers/many writes
 * \version 1.0
 * \note  
 * \date: 2012年08月11日星期六00:28:18
 */ 

#ifndef _CHUNKRING_H_
#define _CHUNKRING_H_

#define CHUNK_NAME_LEN	(96)
#define IS_2PRO(val) !(val & (val-1))

/**
 * main struct
 */
typedef struct _chunk_ring_st{
	char chunk_name[CHUNK_NAME_LEN];	/**< chunk name */
	/* TODO writer last_writer */
	struct {
		unsigned int size;			/**< buffer total size */
		unsigned int mask;			/**< mask to find index */
		volatile unsigned int head; /**<  */
		volatile unsigned int tail; /**<  */
	}prod;
	struct {
		unsigned int size;	
		unsigned int mask;
		volatile unsigned int head;
		volatile unsigned int tail;
	}cons;
	
	char buffer[0];
}chunk_ring_st;

/**
 * \brief init the chunk ring, size must be 2^n
 * \param buffer the chunk buffer include the head
 * \param size the buffer size can be used as a ring
 * \return ...
 */
chunk_ring_st *chunk_ring_init(char *name, char *buffer, unsigned int size);

/**
 * \brief to put data into the ring 
 * \param chunk ring buffer
 * \param data '\0' is not needed
 * \param len the data size
 * \return ...
 */
int chunk_ring_enqueue(chunk_ring_st *chunk, char *data, unsigned int len);

/**
 * \brief to get data from the ring 
 * \param chunk ring buffer
 * \param [out] data  the data will fullfill in it
 * \param [out] len the output data len will be there
 * \return ...
 */
int chunk_ring_dequeue(chunk_ring_st *chunk, char **data, unsigned int *len);


#endif
