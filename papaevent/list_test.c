/**
 * \file list_test.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年06月10日星期一15:06:13
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <Jlog.h>

#include "pap_list.h"

#if CTDEBUG

void print_cb(list_st *pnode, void *arg);

typedef struct _test_head_st{
	int node_nums; 
	list_st index_head;
}test_head_st;

typedef struct _test_st{
	char	radom_char; 
	int 	index;
	list_st index_queue;
}test_st;


int main(int argc, char *argv[])
{
	int total_node = 10;

	if (argc == 2) {
		total_node = atoi(argv[1]);		
	}

	if (total_node <= 0) {
		dblog("test failed!");	
		return -1;	
	}

	int i = 0;
	test_head_st head;		
	test_st *nodes;
	
	head.node_nums = total_node;
	LIST_INIT(head.index_head);
	if (LIST_IS_EMPTY(head.index_head)) {
		dblog("test node init success!");
	}

	for(i = 0; i < total_node; i++) {
		nodes = (test_st*) malloc(sizeof(*nodes));	
		if (nodes == NULL) {
			dblog("alloc new test node failed!");	
			return -1;
		}

		nodes->index = i;
		nodes->radom_char = random()%26;
		LIST_INIT(nodes->index_queue);
		LIST_ADD_TAIL(head.index_head, nodes->index_queue);	
	}

	LIST_TRAVERSE(head.index_head, print_cb, NULL);

	dblog("------------");
	for (i = 0; i < total_node/3; i++) {
		list_st *plist = NULL;

		LIST_DEL_HEAD(head.index_head, plist);				
		if (plist){
			nodes = (test_st *)GET_ENTRY(plist, test_st, index_queue);
			SAFE_FREE(nodes);
		}

		LIST_DEL_TAIL(head.index_head, plist);
		if (plist) {
			nodes = (test_st *)GET_ENTRY(plist, test_st, index_queue);
			SAFE_FREE(nodes);
		}
	}
	LIST_TRAVERSE(head.index_head, print_cb, NULL);

	dblog("------------");
			
	return 0;
}

void print_cb(list_st *pnode, void *arg)
{
	test_st *ptest = (test_st *)GET_ENTRY(pnode, test_st, index_queue); 	
	
	dblog("index[%d], char[%d]", ptest->index, ptest->radom_char);
}

#endif

