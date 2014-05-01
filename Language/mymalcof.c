/**
 * \file mymalcof.c
 * \author  wzj
 * \brief  一个简单的马尔科夫链， 用于制造随机文本。
 * \version 
 * \note  
 * \date: 2013年11月13日星期三22:30:00
 *	1. walk and release!
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define MAX_PREFIX_NUM 		(2)
#define MIN_HASH_SLOT_LEN	(13)
#define TMP_BUF_LEN			(128)
#define NO_WORD				" "

enum create_flag{
	DIC_NODE_CREATE = 1,
	DIC_NODE_LOOKUP = 2
};

/* 后缀结构 */
typedef struct mal_suffix_st{
	char *suffix;
	struct mal_suffix_st *next;
}mal_suffix_st;

/* 马尔科夫字典的节点 */
typedef struct mal_dic_node_st{
	char *prefix[MAX_PREFIX_NUM];		/* 前缀表, 代表一个马尔科夫状态 */
	unsigned int hash_val;				/* 前缀的hash值 */

	mal_suffix_st *suffix_list;			/* 后缀列表，用于表示可能的选择 */	

	struct mal_dic_node_st *next;
}mal_dic_node_st;

/* 马尔科夫字典 */
typedef struct mal_dic_st{
	int slots;
	int total_nodes;
	mal_dic_node_st **hash_table;	
}mal_dic_st;


mal_dic_st *mal_dic_init(int slots)
{
	if (slots <= 0) {
		printf("slots invalid! value=%d\n", slots);	
		return NULL;
	}
	mal_dic_st *mal_dic = NULL;

	mal_dic = (mal_dic_st *) calloc(1, sizeof(*mal_dic));
	if (mal_dic == NULL) {
		printf("create new dic failed! out of memory!\n");	
		goto ERR_EXIT;
	}

	mal_dic->hash_table = (mal_dic_node_st**)calloc(slots, sizeof(mal_dic_node_st *));	
	if (mal_dic->hash_table == NULL) {
		printf("create hash_table slots failed!\n");	
		goto ERR_EXIT;
	}
	
	mal_dic->slots = slots;
	mal_dic->total_nodes = 0;

	return mal_dic;

ERR_EXIT:
	if (mal_dic->hash_table != NULL) {
		free(mal_dic->hash_table);	
		mal_dic->hash_table = NULL;
	}	

	if (mal_dic != NULL) {
		free(mal_dic);	
		mal_dic = NULL;
	}
	return NULL;
}

unsigned int mal_dic_hash(char **prefix_list)
{
	int i = 0, j = 0;	
	char *str = NULL;
	unsigned int hash_val = 0;
	
	for (i = 0; i < MAX_PREFIX_NUM; i++) {
		str = prefix_list[i];
		for (j = 0; j < TMP_BUF_LEN && str[j] != '\0';j++) {
			hash_val = str[j]*33 + (hash_val << 1);
		}	
	}
	
	return hash_val;
}

mal_dic_node_st *mal_dic_new_node(char **prefix_list)
{
	int i = 0;
	mal_dic_node_st *pnode = NULL;	

	pnode = (mal_dic_node_st *)calloc(1, sizeof(*pnode));
	if (pnode == NULL) {
		printf ("init new mal dic node failed!\n");	
		return NULL;
	}

	for (i = 0; i < MAX_PREFIX_NUM && prefix_list[i] != NULL; i++) {
		pnode->prefix[i] = (char *)calloc(1, TMP_BUF_LEN);		
		if (pnode->prefix[i] == NULL) {
			goto ERR_EXIT;	
		}
		strcpy(pnode->prefix[i], prefix_list[i]);
	}

	return pnode;
ERR_EXIT:
	for (i = 0; i < MAX_PREFIX_NUM; i++) {
		if (pnode->prefix[i])
			free(pnode->prefix[i]);	
	}	
	free(pnode);
	
	return NULL;
}

mal_dic_node_st *mal_dic_look_up(mal_dic_st *mal_dic, char **prefix_list, enum create_flag flag)
{
	int index = 0, i = 0;	
	unsigned int hash_val = 0;
	mal_dic_node_st *pnode= NULL;

	hash_val = mal_dic_hash(prefix_list);
	index = hash_val % mal_dic->slots;

	//printf("%u\n", hash_val);
	for (pnode = mal_dic->hash_table[index]; pnode != NULL; pnode = pnode->next) {
		if (pnode->hash_val != hash_val)			
			continue;

		for (i = 0; i < MAX_PREFIX_NUM; i++) {
			if (strcmp(prefix_list[i], pnode->prefix[i]))	
				break;
		}

		if (i >= MAX_PREFIX_NUM)
			break;
	}

	if ((pnode == NULL) && 
		(flag == DIC_NODE_CREATE)) {
		pnode = mal_dic_new_node(prefix_list);	
		if (pnode != NULL) {
			pnode->hash_val = hash_val;

			pnode->next = mal_dic->hash_table[index];		
			mal_dic->hash_table[index] = pnode;
			mal_dic->total_nodes++;
		}
	}

	return pnode;		
}

int mal_dic_add_word(mal_dic_st *mal_dic, char **prefix_list, const char *buf)
{
	mal_suffix_st *psuffix = NULL;
	mal_dic_node_st *pnode = NULL;
	
	pnode = mal_dic_look_up(mal_dic, prefix_list, DIC_NODE_CREATE);
	if (pnode == NULL) {
		printf("look up and init node failed!\n");	
		return -1;
	}

	for (psuffix = pnode->suffix_list; psuffix != NULL; psuffix = psuffix->next) {
		if (!strcmp(buf, psuffix->suffix)) {
			break;	
		}		
	}

	if (psuffix == NULL) {
		psuffix = (mal_suffix_st *)calloc(1, sizeof(*psuffix)+ TMP_BUF_LEN);			
		if (psuffix == NULL) {
			printf("create a new node failed!\n");	
			return -1;
		} 
		psuffix->suffix = (char *)((mal_suffix_st *)psuffix + 1);
		//printf ("%s\n",buf);
		strcpy(psuffix->suffix, buf);
		psuffix->next = pnode->suffix_list;
		pnode->suffix_list = psuffix;
	}

	return 0;	
}

void update_prefix(char **prefix_list, char *buf)
{
	int i = 0;

	for (i = 1; i < MAX_PREFIX_NUM; i++) {
		strcpy(prefix_list[i-1], prefix_list[i]);	
	}

	strcpy(prefix_list[i-1], buf);
}

int mal_dic_build(mal_dic_st *mal_dic, const char *path)
{
	int ret = 0, i = 0;
	char buf[TMP_BUF_LEN] = {'0'};
	char fmt[TMP_BUF_LEN] = {'0'};
	char *prefix_list[MAX_PREFIX_NUM] = {NULL};
	FILE *fp = NULL;
	
	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("open source file failed!");	
		return -1;
	}

	for (i = 0; i < MAX_PREFIX_NUM; i++) {
		prefix_list[i] = (char *) calloc(1, TMP_BUF_LEN);
		if (prefix_list[i] == NULL){
			printf("malloc prefix buffer failed!\n");
			goto ERR_EXIT;	
		}
		strcpy(prefix_list[i], NO_WORD);
	}

	sprintf(fmt, "%%%ds", sizeof(buf));		
	while(fscanf(fp, fmt, buf) > 0){
		ret = mal_dic_add_word(mal_dic, prefix_list, buf);	
		if (ret != 0) {
			printf("add new dic node failed!\n");	
			goto ERR_EXIT;
		}
		update_prefix(prefix_list, buf);
		memset(buf, 0, sizeof(buf));
	}

ERR_EXIT:
	if (fp != NULL) {
		fclose(fp);	
		fp = NULL;
	}	

	for (i = 0; i < MAX_PREFIX_NUM; i++){
		if (prefix_list[i] != NULL) {
			free(prefix_list[i]);	
			prefix_list[i] = NULL;
		}	
	}

	return ret;
}

void mal_dic_destroy(mal_dic_st *mal_dic)
{
	int i = 0, j = 0;
	mal_suffix_st *psuffix = NULL, *ps_next = NULL;
	mal_dic_node_st *pnode = NULL, *pnext = NULL;			

	if (mal_dic == NULL || mal_dic->hash_table == NULL) {
		return ;	
	}

	for(i = 0; i < mal_dic->slots; i++) {
		pnode = mal_dic->hash_table[i];	
		while (pnode != NULL) {
			pnext = pnode->next;	
			
			for (j = 0; j < MAX_PREFIX_NUM; j++) {
				if (pnode->prefix[j]) {
					free(pnode->prefix[j]);	
				}	
			}
			
			psuffix = pnode->suffix_list;	
			while (psuffix != NULL) {
				ps_next = psuffix->next;	
				free(psuffix);
				psuffix = ps_next;
			}
				
			free(pnode);
			pnode = pnext;
		}
	}	

	free(mal_dic->hash_table);
	free(mal_dic);
}

void mal_dic_walk(mal_dic_st *mal_dic)
{
	int i = 0, j = 0;
	mal_dic_node_st *pnode = NULL;
	mal_suffix_st *psuf = NULL;
	
	for (i = 0; i < mal_dic->slots; i++) {
		pnode = mal_dic->hash_table[i];		
		while (pnode != NULL) {
			printf ("%u \n", pnode->hash_val);
			for (j = 0; j < MAX_PREFIX_NUM; j++) {
				if (pnode->prefix[j] != NULL)
					printf ("[%d] prefix[%d]:[%s]\n", i, j, pnode->prefix[j]);	
			}

			j = 0;
			psuf = pnode->suffix_list;
			while (psuf != NULL) {
				printf("----[%d] suffix[%d]:[%s]\n", i, j, psuf->suffix);	
				j++;
				psuf = psuf->next;
			}	
			pnode = pnode->next;	
		}
	}		
}

int mal_word_show(mal_dic_st *pdic, int length)
{
	int ret = 0, times = 0, i = 0, nmatch = 0;
	char *prefix_list[MAX_PREFIX_NUM] = {NULL};			
	char *word = NULL;
	mal_suffix_st *psuffix = NULL;
	mal_dic_node_st *pnode = NULL;

	for (i = 0; i < MAX_PREFIX_NUM; i++) {
		prefix_list[i] = (char *)calloc(1, TMP_BUF_LEN);
		if (prefix_list[i] == NULL) {
			ret = -1;
			goto ERR_EXIT;		
		}
		strcpy(prefix_list[i], NO_WORD);
	}
	
	while (times < length) {
		//printf ("-- %s %s %u\n", prefix_list[0], prefix_list[1], mal_dic_hash(prefix_list));
		pnode = mal_dic_look_up(pdic, prefix_list, DIC_NODE_LOOKUP);			
		if (pnode == NULL) {
			break;	
		}

		nmatch = 0;
		psuffix	= pnode->suffix_list;
		while (psuffix != NULL) {
			if (random()%++nmatch == 0) {
				word = psuffix->suffix;		
			}		
			psuffix = psuffix->next;	
		}

		printf ("%s ", word);
		update_prefix(prefix_list, word);
		if (strstr(word, ".")) {
			times++;	
		}
	}

ERR_EXIT:
	for (i = 0; i < MAX_PREFIX_NUM; i++) {
		if (prefix_list[i] != NULL) {
			free(prefix_list[i]);	
		}	
	}

	return ret;
}

int main(int argc, char *argv[])
{
	char *path = argv[1];
	mal_dic_st *pdic = NULL;

	srand(time(NULL));

	if (path == NULL)
		return 0;
	
	pdic = mal_dic_init(100);

	mal_dic_build(pdic, path);	

	//mal_dic_walk(pdic);

	mal_word_show(pdic, 3);

	mal_dic_destroy(pdic);

	return 0;
}


