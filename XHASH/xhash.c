/**
 * @file  xhash.c
 * @author  wzj
 * @brief it's an hash copy from wxc
 * @version 1.1
 * @note  take care of the detail. ask more why.
 * @date  2012年07月31日星期二22:09:10
 * 
 * the basement is the hardest
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Jlog.h"
#include "xhash.h"

#define SAFE_FREE(p) if(p){		\
			free(p), p = NULL;	\
		}

struct _pair_list{
	int slots;
	int max_nodes;
}my_table[5] = {
	{(1 << 3), 8},
	{(1 << 4), 24},
	{(1 << 5), 180},
	{(1 << 6), 361},
	{(1 << 7), 1024}
	};

unsigned int hash_func_time33(void* key, unsigned int klen)
{
	unsigned int h = 5813;
	unsigned int i = 0;
	char *p = (char*) key;

	while( i++ < klen)
	{
		h = h + p[i]*33;
	}

	return h;
}

int hash_rehash(hash_table_st *ptable)
{
	int i = 0;
	unsigned int new_slots = 0;
	unsigned int new_size = 0;	
	hash_node_st **new_slot = NULL;
	hash_node_st *p = NULL;

	for(i = 0; i < sizeof(my_table)/sizeof(my_table[0]); i++)
	{
		if(my_table[i].slots == ptable->slots)
		{
			new_slots = my_table[i+1].slots;
			new_size = my_table[i+1].max_nodes;
		}
	}
	/* new_slots != 0 new_size != 0 */	
	new_slot = (hash_node_st**)malloc(sizeof(hash_node_st*) * new_slots);
	if(new_slot == NULL)	
		return -1;

	for(i = 0; i < ptable->slots; i++)	
	{
		p = ptable->slot[i];
		while(p)
		{
			hash_node_st *next = p->next;
			int hval = ptable->hash_func(p->key, p->klen);
			int index = hval & (new_slots - 1);

			p->next = new_slot[index];
			new_slot[index] = p;
			p = next;
		}
	}

	ptable->slots = new_slots;	
	ptable->size = new_size;
	SAFE_FREE(ptable->slot);
	
	ptable->slot = new_slot;
	
	return 0;
}

int hash_init_normal(hash_table_st *ptable, hash_func_t hash_func, destroy_func_t destroy)
{
	if(ptable == NULL)
		return -1;

	ptable->slots = my_table[0].slots;
	ptable->size = my_table[0].max_nodes;

	ptable->slot = (hash_node_st **)calloc(ptable->slots, sizeof(hash_node_st));
	if(ptable->slot  == NULL)
		return -1;

	ptable->hash_func = hash_func?hash_func:hash_func_time33;
	ptable->destroy = destroy?destroy:NULL;

	return 0;
}

hash_table_st *hash_init(hash_func_t hash_func, destroy_func_t destroy)
{
	hash_table_st *ptable = NULL; 
	
	ptable = (hash_table_st*)malloc(sizeof(hash_table_st));	
	if(ptable == NULL)
		return NULL;
	ptable->slots = my_table[0].slots;
	ptable->size = my_table[0].max_nodes;

	ptable->slot = (hash_node_st **)calloc(ptable->slots, sizeof(hash_node_st));
	if(ptable->slot  == NULL)
	{
		SAFE_FREE(ptable);
		return NULL;
	}
	ptable->hash_func = hash_func?hash_func:hash_func_time33;
	ptable->destroy = destroy?destroy:NULL;

	return ptable;
}

int hash_insert(hash_table_st *ptable, void *key, unsigned int klen, void*data)
{
	unsigned int hval = ptable->hash_func(key, klen);
	int slot_index = hval & (ptable->slots - 1);
	hash_node_st *p = ptable->slot[slot_index];

	while(p)
	{
		if((p->hash_val == hval) && 
		   (p->klen == klen) &&
		   !(memcmp(p->key, key, klen)))
		{
			if(ptable->destroy)
				ptable->destroy(p->data);
			p->data = data;
			return 0;
		}
		p = p->next;
	}

	hash_node_st* node = NULL;
	node = (hash_node_st*)calloc(1, sizeof(hash_node_st));
	if(node == NULL)
		return -1;
	node->hash_val = hval;

	node->key = (void*)calloc(1, sizeof(char) * klen);
	if(node->key == NULL)
		return -1;
	memcpy(node->key, key, klen);

	node->klen = klen;
	node->data = data;
	node->next = ptable->slot[slot_index];
	ptable->slot[slot_index] = node;

	ptable->nodes++; 
	/**< todo rehash */
	if(ptable->nodes >= ptable->size)
		hash_rehash(ptable);

	return 0;
}

void hash_delete(hash_table_st *ptable, void *key, unsigned int klen)
{
	unsigned int h_val = ptable->hash_func(key, klen);	
	unsigned int slot_index = h_val & (ptable->slots - 1);
	hash_node_st *p = ptable->slot[slot_index];
	hash_node_st *next = p;

	while(p)
	{
		if((p->hash_val == h_val)&&
			(p->klen == klen) &&
			!(memcmp(p->key, key, klen)))
		{
			if(ptable->destroy)
				ptable->destroy(p->data);
			SAFE_FREE(p->key);
			break;
		}
		next = p;
		p = p->next;
	}

	if(p == next)
	{
		ptable->slot[slot_index] = p->next;	
	} else {
		next->next = p->next;
	}

	SAFE_FREE(p);
}

int hash_search(hash_table_st *ptable, void *key, unsigned int klen, void **data)
{
	unsigned int h_val = ptable->hash_func(key, klen);		
	unsigned int slot_index = h_val & (ptable->slots - 1);
	hash_node_st *p = ptable->slot[slot_index];

	while(p)
	{
		if((p->hash_val == h_val) &&
			(p->klen == klen) &&
			!(memcmp(p->key, key, klen)))	
		{
			if(data)
				*data = p->data;
			return 0;
		}
		p = p->next;
	}

	return -1;
}

void hash_destroy(hash_table_st *ptable)
{
	hash_node_st *p = NULL;
	unsigned int i = 0;

	for(i = 0; i < ptable->slots; ++i)
	{
		p = ptable->slot[i];
		while(p)
		{
			hash_node_st *next = p->next;
			if(ptable->destroy)	
				ptable->destroy(p->data);
			SAFE_FREE(p->key);
			SAFE_FREE(p);
			p = next;
		}
	}
	
	SAFE_FREE(ptable->slot);
	SAFE_FREE(ptable);
}

void hash_walk(hash_table_st *ptable, walk_func_t w_func, void *cont)
{
	hash_node_st *p = NULL;	
	unsigned int i = 0;
	if(ptable == NULL)
	{
		WRITELOG("delete failed, ptable is null.");
		return ;
	}

	for(i = 0 ; i < ptable->slots; ++i)
	{
		p = ptable->slot[i];
		while(p)
		{
			cont = w_func(p, cont);
			p = p->next;
		}
	}
}

void hash_status(hash_table_st *ptable, int *state, int len)
{
	unsigned int i = 0;
	hash_node_st *p = NULL;

	for(i = 0; i < ptable->slots; ++i)
	{
		int j = 0;
		p = ptable->slot[i];
		while(p)
		{
			j++;
			p = p->next;
		}
		state[i] = j;
	}
}

void* print_walk(hash_node_st *node, void* cont)
{
	if(node != NULL)
	{
		WRITELOG("%s", (char*)node->data);
	}

	return cont;
}

struct _val_key{
	char *key;
	char *val;	
}val_key[] = {
	{"abc1234", "1ab"},
	{"bcd3223", "2cd"},
	{"af134fd", "3errr"},
	{"adffae2", "4erffa"},
	{"aadffew", "5fcxfa"},
	{"aadffew", "6asdfff"},
	{"aadffew", "7asdfffaa"},
	{"fffffff", "8arrrrrr"},
	{"affcxxx", "9qersdf"},
	{"reqwewq", "10affffz"},
	{"avzzcv", "11avzvzcv"},
	{"fadddd", "12aafadvv"}
		};
//#if XHASH_TEST
#if 1
int main()
{
	hash_table_st *table = NULL;
	int i = 0;
	table = hash_init(NULL, NULL);

	for(i = 0; i < sizeof(val_key)/sizeof(val_key[0]); i++)
	{
		hash_insert(table, val_key[i].key, 7, val_key[i].val);
		WRITELOG("val_key:%s, val_val: %s", val_key[i].key, val_key[i].val);
	}

	WRITELOG("+++++++++++++++++++++++++++++++++++++++++++++++++");
	
	for(i = 0; i < sizeof(val_key)/sizeof(val_key[0]); i++)
	{
		char *data = NULL;
		hash_search(table, val_key[i].key, 7, (void**)&data);
		WRITELOG("val_key:%s, val_val: %s", val_key[i].key, data);
	}

	WRITELOG("+++++++++++++++++++++++++++++++++++++++++++++++++");
	char *t = NULL;
	hash_walk(table, print_walk, t);
#if 0
	for(i = 0; i < 5; i++)
	{
		hash_delete(table, val_key[i].key, 7);
	}
#endif
	WRITELOG("+++++++++++++++++++++++++++++++++++++++++++++++++");
	hash_walk(table, print_walk, t);

	WRITELOG("+++++++++++++++++++++++++++++++++++++++++++++++++");
	int stat[50] = {0};
	hash_status(table, stat, 50);
	for(i = 0; i < 50; i++)
	{
		WRITELOG("cont:%d", stat[i]);
	}

	return 0;
}

#endif
