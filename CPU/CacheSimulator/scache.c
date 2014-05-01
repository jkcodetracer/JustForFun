/**
 * \file scache.c
 * \author  wzj
 * \brief  simulator of the Direct mapped cache
 * \version 
 * \note  
 * \date: 2013年07月14日星期日20:10:42
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <Jlog.h>

/* address: |tag|set|block| */
/* cache line: |valid|tag|blocks| */
/* in the direct mapped cache, there is only one cache line in the set. */
/* (S, E, B, m) = (4, 1, 2, 4) ==bits== (s, e, b, m) = (2, 0, 1, 4) 
	we store the bits here.
*/
typedef struct cache_sys{
	int bits_set;	
	int bits_block;
	int bits_address;	
	int bits_tag;

	int bits_extract;	/* for the direct mapped cache, it's 0. */

	int miss_statistic;	/* statistic the cache miss. */
	int cache_line_length;
	char *cache_sets;
}cache_st;

/* the main memory */
char *memory = NULL;

int bitmask(int bits)
{
	return (1 << bits) - 1;
}

int bits2int(int bits)
{
	return  1 << bits;
}

int map_index(int address, int bits, int offset)
{
	return (address >> offset) & bitmask(bits);
}

/**
 * \brief init the cache, with the (s, e, b, m)
 * \param s	: the set bits.
 *		  e : the cache line number of the set.
 *		  b : the blocks bits in one cache line	
 *		  m : the system address bits.
 * \return  cache_st *: success
 *			NULL: failed
 */
cache_st *cache_init(int s, int e, int b, int m)
{
	int capability = 0;
	cache_st *pcache = NULL;
	
	capability = bits2int(s) * bits2int(e) * bits2int(b);
	pcache = (cache_st *) calloc(1, sizeof(*pcache) + 					/* the manager */
								 capability * sizeof(char) + 			/* the blocks */
								 2 * sizeof(int)*bits2int(s)*bits2int(e)  /* for |valid|tag| on each cache line */
								 );
	if (pcache == NULL) {
		printf("init cache_st failed!\n");	
		return NULL;
	}

	pcache->bits_set = s;
	pcache->bits_block = b;
	pcache->bits_address = m;
	pcache->bits_tag = m - s - b;
	pcache->bits_extract = e;
	pcache->cache_sets = (char*)(pcache + sizeof(*pcache));
	pcache->cache_line_length = 2 * sizeof(int) + bits2int(b);

	return pcache;
}
/** 
 * \brief: destroy the cache
 *
 */
void cache_destroy(cache_st *cache)
{
	if (cache != NULL) {
		free (cache);	
	}
}
/**
 * \brief: if the cache miss, we lookup the memory
 * \return the hit result or the null.
 */
char *memory_lookup(int address)
{
	return memory + address;
}

/**
 * \brief: lookup the cache for the data in the main memory
 * \return the hit result 
 * \note as a contract, we hit one char one time.
 */
char *cache_lookup(cache_st *cache, int address)
{
	int set_index = 0;	
	int addr_tag = 0;
	int block_index = 0;

	char *cache_line = NULL;	/* mapped cache_line */
	
	set_index = map_index(address, cache->bits_set, cache->bits_block);
	block_index = map_index(address, cache->bits_block, 0);
	addr_tag = map_index(address, cache->bits_tag, cache->bits_block + cache->bits_set);	
	
	if (set_index >= bits2int(cache->bits_set)){
		printf("out of the cache line max index!\n");	
		return NULL;
	}
		
	/* begin to lookup */	
	cache_line = cache->cache_sets + set_index * cache->cache_line_length;
	if (*(int*)cache_line == 1 && 
		*((int*)cache_line + 1) == addr_tag) { 
		/* cache hit */
		cache_line = cache_line + 2*sizeof(int);	/* jump the valid and tag part */
		return cache_line + block_index;
	}
	cache->miss_statistic ++;
	/* cache miss, fill a cache line */
	char *pblock_begin = memory_lookup(address & ~bitmask(cache->bits_block));				
	memcpy(cache_line + 2*sizeof(int), pblock_begin, bits2int(cache->bits_block));	
	*(int*)cache_line = 1;
	*((int*)cache_line + 1) = addr_tag;
	
	cache_line = cache_line + 2*sizeof(int);
	return cache_line + block_index;
}

char *memory_init(int bits_address)
{
	int i = 0;
	int memory_size = bits2int(bits_address);
	char *pmemory = NULL;

	pmemory = (char* )calloc(1, sizeof(char) * memory_size);
	if (pmemory == NULL) {
		printf("init memory failed!\n");	
		return NULL;
	}

	for (i = 0; i < memory_size; i++) {
		pmemory[i] = i;	
	}

	return pmemory;
}

void cache_dump(cache_st *cache)
{
	int i = 0, j = 0;;
	int blocks = bits2int(cache->bits_block);
	int total_line_num = bits2int(cache->bits_set);		
	char *pline = cache->cache_sets;

	printf("current cache line: total miss:%d \n", cache->miss_statistic);
	
	for (i = 0; i < total_line_num; i++){
		pline = cache->cache_sets + i * cache->cache_line_length;	
		
		printf("set:%d valid:%d tag: %x \t", i, *(int*)pline, *((int*)pline + 1));
		pline = pline + sizeof(int) * 2;
		for (j = 0; j < blocks; j++) {
			printf("%d ", pline[j]);	
		}	
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int b_set = 2;
	int b_block = 2;
	int b_address = 5;
	int total_test = atoi(argv[1]);

	cache_st *test_cache = cache_init(b_set, 0, b_block, b_address);
	if (test_cache == NULL) {
		printf("init cache_st failed!\n");	
		return -1;
	}

	memory = memory_init(b_address);
	if (memory == NULL) {
		printf("init memory failed!\n");	
		return -1;
	}

	int i = 0;
	int address = 0;
	srand(time(NULL));
	cache_dump(test_cache);
	for (i = 0; i < total_test; i++) {
		address = rand()%(bits2int(b_address));	
		char *data = cache_lookup(test_cache, address);
		printf("address: %d  date: %d \n", address, *data);
		cache_dump(test_cache);
	}

	cache_destroy(test_cache);
	test_cache = NULL;

	return 0;
}







