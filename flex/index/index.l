/**
 * \file index.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月10日星期四07:11:30
 * 
 * discript your detail info.
 */ 

%option noyywrap nodefault yylineno case-insensitive

%{
#include <stdio.h>
#include <stdlib.h>
#include <Jlog.h>

typedef struct _index_st{
	char 	*filename;
	int 	linepos;
	int 	lineno;	
	struct _index_st *next;
}index_st;

typedef struct _syb_table_st{
	char 	*symble;
	unsigned int 	hash_val;
	struct _index_st *index;
}syb_table_st;

syb_table_st * lookup(char *symble);
int add_new(char *symble, char *filename, int lineno, int linepos);

#define TABLE_MAX	(9999)

syb_table_st table[TABLE_MAX];
char *current_file;

%}

%%

[a-z]+ {add_new(yytext, current_file, yylineno, 0);}
.|\n

%%

unsigned int simple_hash(const char *symble)
{
	if(symble == NULL)
		return 0;
	unsigned int hash_val = 0;	
	const char *p = symble;

	while(p != NULL && *p != '\0') {
		hash_val = hash_val * 33 + *p;	
		p++;
	}

	return hash_val;
}

syb_table_st *lookup(char *symble)
{
	ASSERT(symble, NULL);
	syb_table_st *p = NULL;
	unsigned int hash_val = 0;	
	unsigned int index = 0;
	int count = 0;
	
	hash_val = simple_hash(symble);
	index = hash_val % TABLE_MAX;
	
	for(count = 0; count < TABLE_MAX; count++) {
		if(table[index].symble == NULL) {
			p = &table[index];	
			p->symble = strdup(symble);
			p->hash_val = hash_val;
			break;
		}	
		//printf("conflict: loop[%d]\n", count);
		if(	hash_val == table[index].hash_val &&
			!strcmp(table[index].symble, symble)){
			p = &table[index];	
			break;
		}

		index++;
		if(index >= TABLE_MAX) {
			index = 0;	
		}
	}

	return p;
}

int add_new(char *symble, char *filename, int lineno, int linepos)
{
	ASSERT(symble && filename && lineno >= 0, -1);
	syb_table_st *p = NULL;	
	index_st 	 *newnode = NULL;
	//printf("new word:[%s]\n", symble);
	p = lookup(symble);
	if(p == NULL) {
		printf("alloc new node failed!\n");	
		return -1;
	}

	if(	p->index &&
		p->index->lineno == lineno &&
		p->index->filename == filename)
		return -1;
	
	newnode = (index_st *)malloc(sizeof(index_st));
	if(newnode == NULL) {
		printf("alloc new node failed!\n");	
		return -1;
	}
	
	newnode->lineno = lineno;
	newnode->filename = filename;
	newnode->next = p->index;	
	p->index = newnode;

	return 0;
}

void printf_all()
{
	index_st *pst = NULL, *pstn = NULL, *pstp = NULL;	
	int i = 0;

	for(i = 0; i < TABLE_MAX; i++) {
		if(table[i].symble == NULL) {
			continue;	
		}	
		printf("[%s]\n", table[i].symble);
		pstn = pstp = NULL;
		pst = table[i].index;
		do{
			pstn = pst->next;	
			pst->next = pstp;
			pstp = pst;
			pst = pstn;
		}while(pst);	

		table[i].index = pstp;

		for(pst = table[i].index; pst != NULL; pst = pst->next) {
			printf("[%s:%d]", pst->filename, pst->lineno);
		}
		printf("\n\n");
	}
}

int main(int argc, char *argv[])
{
	if(argc <= 1) {
		printf("two few arg!\n");	
		return -1;
	}
	int i = 0;

	for(i = 1; i < argc; i++) {
		if(argv[i] == NULL) {
			printf("no avilable path!\n");	
			return -1;	
		}	

		FILE *fp = fopen(argv[i], "r");
		if(fp == NULL) {
			printf("the new fp is null!\n");	
			return -1;
		}

		current_file = argv[i];
		yyrestart(fp);	
		yylineno = 1;
		yylex();

		fclose(fp);
		fp = NULL;
	}

	printf_all();
}
