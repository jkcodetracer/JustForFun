/**
 * \file vm.h
 * \author  wzj
 * \brief  存储结构的简单模拟， CPU -- MMU -- CACHE -- Physical Memory
 *	对于虚拟地址和物理地址的转换
 * \version 
 * \note  
 * \date: 2013年10月01日星期二19:20:17
 */ 
#ifndef _VIRTUAL_MEMORY_SYSTEM_H
#define _VIRTURL_MEMORY_SYSTEM_H

typedef struct cache_set_st{
	unsigned int cache_tag;			/* 当前cache的标记 */ 
	unsigned int valid;				/* 当前cache是否有效 */
	unsigned int *blocks;			/* 当前set的block列表 */
}cache_set_st;

typedef struct cache_system_st{
	/* physical address: 	|ppn		| ppo						| */
	/* cache map:		 	|catch tag	| cache index | cache offset| */
	unsigned int cache_tag_bits;	/* cache 标记占的总位数 */
	unsigned int cache_index_bits;	/* cache index 的总位数 */
	unsigned int cache_offset_bits;	/* cache offset的总位数 */

	/* cache item */
	unsigned int cache_set_num;		/* cache总数 */
	unsigned int cache_way_num;		/* cache的路数 */
	cache_set_st *cache_sets;		/* cache sets列表 */
}cache_system_st;

typedef struct pte_system_st{
	unsigned int ppn_bits;			/* physical page number 总位数 */	
	
	/* pte : | ppn | valid | */
	/* 这里使用最简单的一级pte */
	unsigned int pte_num;			/* pte的总数,  因为是一级的，所以pte_num 就是vpn的总数 */ 
	unsigned int *pte_items;		/* pte item 数组，总数为pte_num */
}pte_system_st;

typedef struct tlb_system_st{
	/* virtual address:  | vpn 					| vpo | */
	/* map to tlb: 		 | tlb_tag	| tlb_index | vpo | */
	/* 位的对应关系如上图 */
	unsigned int tlb_index_bits;	/* tlb set的下标总位数， 用于确认需要查哪个tlb set */
	unsigned int tlb_tag_bits;		/* tlb标记位总位数，用于确认匹配的table entry */
	unsigned int vpo_bits;			/* 与vm_system_st中的vpo_bits同义, 查询tlb时，不会使用 */
	 
	/* tlb本身有些像cache 的构造 */
	/* tlb最重要的目的就是查到ppn, 这个ppn是在page table中的, 这里直接缓存到了tlb中 */
	/*一个tlb的set:		| tlb_tag | ppn | valid | * tlb_way_num */
	/* tlb本身的属性 */
	unsigned int tlb_set_num;		/* tlb的set总数 */
	unsigned int tlb_way_num;		/* tlb的路数 */
	unsigned int *tlb_items;		/* 由set 与 way的乘积决定，使用index和tag来索引 */
}tlb_system_st;

typedef struct vm_system_st{
	/* vpo == ppo, always! */
	/* virtual address:  | vpn | vpo | */
	unsigned int va_bits;			/* 虚拟地址总位数 */
	unsigned int vpn_bits;			/* virtual page number 总位数 */
	unsigned int vpo_bits;			/* virtual page offset 总位数 */
	 
	/* physical address: | ppn | ppo | */
	unsigned int pa_bits;			/* 物理地址总位数 */
	unsigned int ppn_bits;			/* physical page number 总位数 */
	unsigned int ppo_bits;			/* physical page offset 总位数 */

	tlb_system_st *vm_tlb;			/* 模拟的tlb系统 */
	pte_system_st *vm_pte;			/* 模拟的单级pte */
	cache_system_st *vm_cache;		/* cache 信息 */	
}vm_system_st;

#endif 
