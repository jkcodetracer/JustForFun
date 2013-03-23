/**
 * \file calc_main.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月03日星期日00:13:37
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "calc_head.h"

#include <Jlog.h>

struct ast* newast(int nodetype, struct ast* l, struct ast *r)
{
	struct ast *a = (struct ast*)calloc(1, sizeof(struct ast));	

	if(!a) {
		yyerror("out of space!");		
		exit(0);
	}

	a->nodetype = nodetype;
	a->l = l;
	a->r = r;

	return a;
}

struct ast *newnum(double d)
{
	struct numval *a = (struct numval*) calloc(1, sizeof(struct numval));

	if(!a) {
		yyerror("out of space!");	
		exit(0);
	}

	a->nodetype = 'K';
	a->number = d;

	return (struct ast*)a;
}

double 
eval(struct ast *a)
{
	double v = 0;	

	if(!a) {
		printf("ast is null return error!\n");	
		return -1;
	}
	
	switch(a->nodetype) {
		case 'K': v = ((struct numval*)a)->number;break;	
		case '+': v = eval(a->l) + eval(a->r);break;
		case '-': v = eval(a->l) - eval(a->r);break;
		case '*': v = eval(a->l) * eval(a->r);break;
		case '/':  {
			double tmp = eval(a->r);	
			
			if(tmp == 0) {
				printf("float overflow!\n");		
				return -1;
			}

			v = eval(a->l) / tmp;
			break;
		}
		case '|': v = eval(a->l); if(v < 0) v = -v; break;
		case 'M': v = -eval(a->l); break; 	
		default: printf("internal error: bad node %c\n", a->nodetype);
	}

	return v;
}

void 
treefree(struct ast *a)
{
	switch(a->nodetype) {
		case '+':
		case '-':
		case '*':
		case '/':
			treefree(a->r);
		case '|':
		case 'M':
			treefree(a->l);
		case 'K':
			free(a);
			break;
		default: 
			printf("internal error: free bad node %c\n", a->nodetype);
	}
}

void
yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d:error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}


int 
main(int argc, char *argv[])
{
	printf("> ");
	return yyparse();
}



