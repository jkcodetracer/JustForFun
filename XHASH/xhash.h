/**
 * @file  xhash.h
 * @author  wzj
 * @brief  xhash head
 * @version 1.1
 * @note  
 * @date: 2012年07月31日星期二22:26:23
 * 
 */ 
#ifndef _X_HASH_
#define _X_HASH_

/**
 * show your better hash func.
 */
typedef unsigned int (*hash_func_t)(void* key, unsigned int klen);
/**
 * if you use it, hash table will help you free memory.
 */
typedef int (*destroy_func_t)(void* data);

/**
 * There is no hash slot just head and node.
 */
typedef struct  _hash_node_st{
	unsigned int hash_val;		/**< store the hash value. */
	void* key;					/**< the hash main key. */
	unsigned int klen;			/**< the main key len. */
	void* data;					/**< the values. */
	struct _hash_node_st *next; /**< to maintan the single chain. */
}hash_node_st;

/**
 * this struct is the hash table main, 
 */
typedef struct _hash_table_st{
	hash_node_st **slot;		/**< the slot chain. */
	unsigned int slots;			/**< the numbers of slot. */
	unsigned int size;			/**< total nodes number. */
	unsigned int nodes;			/**< current nodes in the table. */

	hash_func_t hash_func;		/**< if it is null, it will get a default value. */
	destroy_func_t destroy;		/**< it can be null. */
}hash_table_st;

typedef void *(*walk_func_t)(hash_node_st* element, void* cont);

/**
 * \brief create a hash table 
 * \param [in] hash_func self defined hash function.
 * \param [in] destroy when you call the hash_delete/hash_destroy, it will free 
 * all the values
 * \return NULL create failed
 * \return !NULL a hash table can be used
 *
 * \see hash_delete
 * \see hash_destroy
 */
hash_table_st *hash_init(hash_func_t hash_func, destroy_func_t destroy);

/**
 * \brief insert a key-value pair into the hash
 * \param [in|out] ptable main hash table... 
 * \param [in] key to locate a place in the table
 * \param [in] klen the key len
 * \param [in] data the stored value
 * \return 0 sucess
 * \return !0 failed
 */
int hash_insert(hash_table_st *ptable, void *key, unsigned int klen, void *data);

/**
 * \brief delete a key from the hashtable, and destroy the hash node and its value
 * \param [in] ptable
 * \param [in] key
 * \param [in] klen
 */
void hash_delete(hash_table_st *ptable, void *key, unsigned int klen);

/**
 * \brief get the item from the hash table. 
 * \param [in] ptable
 * \param [in] key 
 * \param [in] klen
 * \param [in|out] data if find the values, we use the data to return the value
 * \return 0 sucess
 * \return !0 failed
 */
int hash_search(hash_table_st *ptable, void *key, unsigned int klen, void **data);

/**
 * \brief delete all the hash table.
 * \param ptable hash table to be destroy
 */
void hash_destroy(hash_table_st *ptable);
/**
 * \brief walk hash
 * \param w_func tranvers function
 * \param cont context
 */
void hash_walk(hash_table_st *ptable, walk_func_t w_func, void *cont);
/**
 * \brief rehash
 * \param ptable hash table
 * \return 0 success -1 failed
 */
int hash_rehash(hash_table_st *ptable);
/**
 * \brief see echo slot got how many nodes
 * \param ptable hash table
 * \param state state contenner
 * \param len the len of the state
 * \return 0 success -1 failed
 */
void hash_status(hash_table_st *ptable, int *state, int len);

/**
 * \brief hash init you should get one first
 * \param
 * \note fate function, don't use it 
 */
int hash_init_normal(hash_table_st *ptable, hash_func_t hash_func, destroy_func_t destroy);


#endif

