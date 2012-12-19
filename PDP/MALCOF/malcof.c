/*
 * @FileName: malcof.c
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
 * @Date: 2012年03月18日星期日08:39:30
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

enum {
	NPREF = 2,
	NHASH = 4093,
	MAXGEN = 10000
};

typedef struct State{
	char *pref[NPREF];	
	struct Suffix *suf;
	struct State *next;
}State;

typedef struct Suffix{
	char *word;
	struct Suffix *next;
}Suffix;

State  *state_tab[NHASH] = {0};
static char NONWORD[] = "ab";

unsigned int hash(char *s[])
{
	unsigned int h = 0;
	unsigned char *p;
	int i = 0;

	for(i = 0; i < NPREF; i++)
	{
		for(p =(unsigned char*) s[i]; *p != '\0'; p++)
		{
			h = h * 3 + *p;
		}
	}

	return h%NHASH;
}

State *lookup(char* prefix[], int create)
{
	int i , h;
	State *st = NULL;

	h = hash(prefix);
	for(st = state_tab[h]; st != NULL; st = st->next)	
	{
		for(i = 0; i < NPREF; i++)
		{
			if(strcmp(st->pref[i], prefix[i]))
			{
				break;
			}
		}
		if(i == NPREF)
		{
			break;
		}
	}
	
	if ((st == NULL) && create)
	{
		st = (State*)malloc(sizeof(State));
		for(i = 0; i < NPREF; i++)
		{
			st->pref[i] = prefix[i];
		}
		st->suf = NULL;
		st->next = state_tab[h];
		state_tab[h] = st;
	}
	return st;
}

void addsuffix(State *st, char* suffix)
{
	Suffix *suf;

	suf = (Suffix*) malloc(sizeof(Suffix));
	suf->word = suffix;
	suf->next = st->suf;
	st->suf = suf;
}

void add(char *prefix[], char *suffix)
{
	State *st = NULL;

	st = lookup(prefix, 1);
	addsuffix(st, suffix);

	memmove(prefix, prefix + 1, (NPREF - 1)*sizeof(prefix[0]));
	prefix[NPREF-1] = suffix;
}

void build(char *prefix[], FILE *f)
{
	char buf[30], fmt[10];

	sprintf(fmt, "%%%ds", sizeof(buf)-1);

	while(fscanf(f, fmt, buf) != EOF)
	{
	//	printf("[:]%s[:]%s\n", prefix[1], buf);
		add(prefix, strdup(buf));
	}
}

void generate(int nwords, int sand)
{
	char *w = NULL;
	char *prefix[NPREF] ;
	State *st = NULL;
	Suffix *suf = NULL;
	int i = 0;
	int nmatch = 0;

	for(i = 0; i < NPREF; i++)
	{
		prefix[i] = NONWORD;
	}
	srand(time(0));

	for(i = 0; i < nwords; i++)
	{
		st = lookup(prefix, 0);	
		nmatch = 0;
		if (st == NULL)
		{
			printf("st is empty, prefix:%s %s\n", prefix[0], prefix[1]);
			break;
		}
		if (st->suf == NULL)
		{
			printf("suf....null");
		}
		for(suf = st->suf; suf != NULL; suf = suf->next)
		{
			//very strange, when i use the  if(rand()%(++nmatch)) case the core dump...always.. hehe, as you see 165 --168  value w maybe empty...
			if(((int)rand()%(++nmatch)) == 0)
			{
				w = suf->word;
			}
		}
		if (w == NULL)
		{
			continue;	
		}
		if(strcmp(w, NONWORD) == 0 ) 
		{
			break;
		}
		printf("%s ", w);
		memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
		prefix[NPREF - 1] = w;
	}
}

int main()
{
	int i, 	nwords = 15;
	char *prefix[NPREF];
	FILE* fp;
	
	fp = fopen("joker.txt","r");

	for(i = 0 ; i < NPREF; i++)
		prefix[i] = NONWORD;

	build(prefix, fp);
	add(prefix, NONWORD);

	/*for (i = 0; i < 4093; i++)
	{
		if (state_tab[i] != NULL)
		{
			printf("%s\n", state_tab[i]->pref[0]);
		}
	}*/
	//srand(100);
	generate(nwords, i)
	printf("\n");
	fclose(fp);

	return 0;
}

