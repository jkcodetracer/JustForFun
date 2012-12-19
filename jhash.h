/*
 * @FileName: jhash.h
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年03月18日星期日00:34:40
 * 
 */ 

typedef struct jHASH_NODE{
	void *data;	
	HASH_NODE * next;
}HASH_NODE;

typedef struct jHASH{
	int block_size;
	void* (*destroy)();
	void* blocks;		
}HASH;

create_hash();
