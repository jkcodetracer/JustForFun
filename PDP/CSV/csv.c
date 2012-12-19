/*
 * @FileName: csv.c
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
 * @Date: 2012年03月15日星期四23:27:36
 * 
 */ 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#define SAFEFREE(ptr) do{	\
			if (ptr)		\
			{free(ptr);ptr = NULL;}	\
		}while(0)  

 enum {
 	NOMEM = -2 
 };

static char *line = NULL;
static char *sline = NULL;
static int  max_field = 0;
static char **field = NULL;
static int n_field = 0;

static int max_line = 0;
static char fill_sep[] = ",";

static void reset(void)
{
	int i = 0;

	SAFEFREE(line);
	SAFEFREE(sline);

/*	if (field)
	{
		for(i = 0; i < max_field; i++)
		{
			SAFEFREE(field[i]);
		}*/
		SAFEFREE(field);
//	}
	max_line = max_field = n_field;
}

static int endofline(FILE *fin, int c)
{
	int eol;

	eol = (c == '\r' || c == '\n');
	if (c == '\r')
	{
		c = getc(fin);
		if (c != '\n' && c != EOF)
			ungetc(c, fin);
	}
	return eol;
}
char *advquoted(char* ptr)
{
	if (ptr == NULL)
	{
		return NULL;
	}
	int i , j;
	
	for (i = j = 0; ptr[i] != '\0'; i++, j++)
	{
		if (ptr[i] == '"' && ptr[++i] != '"')
		{
			int k = strcspn(ptr + i, fill_sep);	
			memmove(ptr + j, ptr + i, k);
			j += k;
			i += k;
			break;
		}
		//如果一节由多个""开头，那么过滤掉，只剩一个。
		//有问题
//			ptr[j] = ptr[i];
	}
	ptr[j] = '\0';
	return ptr + i;
}

static int split(void)
{
	char *p = NULL;
	char *cur = NULL;
	char **newf = NULL;
	char sepc; 
		
	n_field = 0;
	if (line[0] == '\0')
	{
		return 0;
	}
	strcpy(sline, line);
	p = sline;
	cur = sline;

	do	{		if (n_field >= max_field)		
				{			
					max_field *=2;			
					newf = (char**)realloc(field,max_field *sizeof(field[0]));	
					if (newf == NULL)		
					{		
						return NOMEM;	
					}	
					field = newf;		
				}	

		if (*p == '"')
		{
			cur = advquoted(++p);
		}
		else
		{
			cur = p + strcspn(p, fill_sep);
		}
		sepc = cur[0];	
		cur[0] = '\0';	
		field[n_field++] = p;
		p = cur + 1;
	}while(sepc == ',');

	return n_field;
}
char *csvgetline(FILE* fin)
{
	if (fin == NULL)
	{
		return NULL;
	}
	int i, c;
	char* newl, *news;

	if (line == NULL)
	{
		max_field = max_line = 1;
		line = (char*) malloc(max_line);
		sline = (char*) malloc(max_line);
		field = (char**) malloc(max_field * sizeof(field[0]));
		if (line == NULL || sline == NULL || field == NULL)
		{
			reset();
			return NULL;
		}
	}

	for (i = 0; (c = getc(fin)) != EOF && !endofline(fin, c); i++)
	{
		if (i >= max_line - 1)
		{
			max_line *= 2;
			newl = (char*)realloc(line, max_line);
			news = (char*)realloc(sline, max_line);

			if (newl == NULL 
				|| news == NULL)
			{
				reset();
				return NULL;
			}
			line = newl;
			sline = news;
		}
		line[i] = c;
	}

	line[i] = '\0';
	if (split() == NOMEM)
	{
		reset();
		return NULL;
	}	
	return (c == EOF && i == 0)? NULL:line;
}

int csvgetnfeild()
{
	return  n_field;
}

char* csvgetfeild(int n)
{
	if (field != NULL && field[n] != NULL)
	{
		return field[n];
	}
	return NULL;
}
