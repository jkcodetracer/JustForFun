/**
 * \file calc.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月12日星期二23:55:49
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "calc.h"

void treefree(ast_st *past);
void listfree(param_st *plist);

ast_st *newast(int type, ast_st *l, ast_st *r)
{
	ast_st *pnew = NULL;

	pnew = (ast_st *)malloc(sizeof(ast_st));
	if(pnew == NULL) {
		printf("alloc new ast failed!\n");	
		return NULL;
	}

	pnew->nodetype = type;
	pnew->l = l;
	pnew->r = r;

	return pnew;
}

ast_st *newcmp(int nodetype, ast_st *l, ast_st *r)
{
	cmp_st *pcmp = NULL;

	pcmp = (cmp_st*) malloc(sizeof(cmp_st));
	if(pcmp == NULL) {
		printf("alloc new cmp_st failed!\n");	
		return NULL;
	}

	pcmp->nodetype = '0' + nodetype;
	pcmp->l = l;
	pcmp->r = r;

	return (ast_st *)pcmp;
}

ast_st *newnum(double d)
{
	num_st *pnew = NULL;
	
	pnew = (num_st *)malloc(sizeof(num_st));
	if(pnew == NULL) {
		printf("alloc new num_st failed!\n");	
		return NULL;
	}

	pnew->nodetype = 'N';
	pnew->number = d;

	return (ast_st *) pnew;
}

void yyerror(char *s, ...)
{
	va_list ap;

	va_start(ap, s);
	fprintf(stderr, "%d: error:", yylineno);
	vfprintf(stderr, s, ap);
	va_end(ap);

	fprintf(stderr, "\n");
}

ast_st *newname(symbol_st *name)
{
	name_st *pname = NULL;

	pname = (name_st *)malloc(sizeof(name_st));
	if(pname == NULL) {
		yyerror("malloc new name failed!");	
		return NULL;
	}

	pname->nodetype = 'S';
	pname->sym = name;

	return (ast_st *)pname;
}

ast_st *newsymlist(symbol_st *name, param_st *pparam)
{
	param_st *pnew = NULL;

	pnew = (param_st *)malloc(sizeof(param_st));
	if(pnew == NULL) {
		yyerror("malloc new param list failed!");	
		return NULL;
	}
	pnew->sym = name;
	pnew->next = pparam;

	return (ast_st *)pnew;
}

ast_st *newcall(symbol_st *name, ast_st *plist)
{
	cfunc_st *pcall = NULL;

	pcall = (cfunc_st *)malloc(sizeof(cfunc_st));
	if(pcall == NULL) {
		yyerror("malloc new pcall failed!");	
		return NULL;
	}

	pcall->nodetype = 'C';
	pcall->func = name;
	pcall->plist = plist;	

	return (ast_st*)pcall;
}

unsigned int hash_value(char *str)
{
	unsigned int hash_val = 0;

	while(*str++ != '\0') {
		hash_val = (hash_val+33) << 5 + *str;	
	}

	return hash_val;
}


symbol_st *lookup(char *name)
{
	int total = NHASH;
	symbol_st *psym = NULL;

	if(name == NULL) {
		yyerror("invalid input name!");		
		return NULL;
	}

	psym = &symbol_table[hash_value(name)%NHASH];	
	while(total-- > 0) {
		if(psym->name == NULL) {
			psym->name = strdup(name);		
			return psym;
		} else if(!strcmp(psym->name, name)) {
			return psym;	
		}
		psym++;
		if(psym >= symbol_table + NHASH)
			psym = symbol_table;
	}

	yyerror("the hash table is full!");
	exit(0);
}

double dousercall(ast_st *ucall)
{
	if(ucall == NULL){
		yyerror("do user function call failed!");	
		return -1;
	}
	
	symbol_st *pfuncname = ((cfunc_st*)ucall)->func;
	ast_st *pnewparam = ((cfunc_st *)ucall)->plist;
	param_st *poldlist = pfuncname->plist;
	double *pnewvalue = NULL;
	double *poldvalue = NULL;
	double v = 0;

	/* get the params's total number */	
	param_st *pparam = NULL;
	int paramnum = 0;	
	int i = 0;
	
	pparam = poldlist;
	while(pparam != NULL) {
		paramnum++;
		pparam = pparam->next;
	}

	pnewvalue = (double *)malloc(sizeof(double)*paramnum);
	if(pnewvalue == NULL) {
		yyerror("alloc param store failed!");	
		return -1;
	}

	poldvalue = (double *)malloc(sizeof(double)*paramnum);
	if(poldvalue == NULL) {
		yyerror("alloc param store failed!");	
		return -1;
	}
	/* get current param's value */
	for(i = 0; i < paramnum; i++) {
		if(pnewparam == NULL) {
			yyerror("the number list is error matched!");
			free(pnewvalue);	
			return -1;
		}

		if(pnewparam->nodetype == 'L') {
			pnewvalue[i] = eval(pnewparam->l);	
			pnewparam = pnewparam->r;
		} else {
			pnewvalue[i] = eval(pnewparam);	
			pnewparam = NULL;
		}
	}	
	
	/* replace the arguments */
	pparam = poldlist;
	for(i = 0; pparam; i++){
		poldvalue[i] = pparam->sym->value;			
		pparam->sym->value = pnewvalue[i];
		pparam = pparam->next;
	}
	
	v = eval(pfuncname->func);
	/* restore the value. */	
	pparam = poldlist;
	for(i = 0; pparam; i++) {
		pparam->sym->value = poldvalue[i];	
		pparam = pparam->next;
	}

	free(poldvalue);
	free(pnewvalue);

	return v;
}

void dodef(symbol_st *name, param_st *plist, ast_st *func)
{
	if(name->func != NULL) 
		treefree(name->func);	
	if(name->plist != NULL)
		listfree(name->plist);

	name->func = func;
	name->plist = plist;
}

double eval(ast_st *past)
{
	double result = 0.0;

	if(past == NULL) {
		printf("eval internal error!\n");	
		return 0.0;
	}
	/* 修改成表驱动的， 效率会更高. */
	switch(past->nodetype){
	case 'N':
		result = ((num_st*)past)->number;	
		break;
	case '+':
		result = eval(past->l) + eval(past->r);
		break;
	case '-':
		result = eval(past->l) - eval(past->r);
		break;
	case '*':
		result = eval(past->l) * eval(past->r);
		break;
	case '/':
		result = eval(past->l) / eval(past->r);
		break;
	case 'M':
		result = -eval(past->l);
		break;
	case '0': result = eval(((cmp_st*)past)->l) > eval(((cmp_st*)past)->r)? 1:0; break;
	case '1': result = eval(((cmp_st*)past)->l) < eval(((cmp_st*)past)->r)? 1:0; break;
	case '2': result = eval(((cmp_st*)past)->l) >= eval(((cmp_st*)past)->r)? 1:0; break;
	case '3': result = eval(((cmp_st*)past)->l) <= eval(((cmp_st*)past)->r)? 1:0; break;
	case '4': result = eval(((cmp_st*)past)->l) == eval(((cmp_st*)past)->r)? 1:0; break;
	case '5': result = eval(((cmp_st*)past)->l) != eval(((cmp_st*)past)->r)? 1:0; break;

	case 'S':
		result = ((name_st*)past)->sym->value;
		break;
	case 'C':
		result = dousercall(past);
		break;
	case 'L':
		eval(past->l);	/* it meaning less... */
		result = eval(past->r);
		break;
	default:
		printf("match state error!\n");
		break;
	}

	return result;
}

void treefree(ast_st *past)
{
	if(past == NULL) {
		return;	
	}

	switch(past->nodetype) {
		case '+':	
		case '-':
		case '*':
		case '/':
			treefree(past->r);

		case 'M':
			treefree(past->l);	
			break;
		case 'S': 
		{
			symbol_st *tmpsym = NULL;
			tmpsym = ((name_st *)past)->sym;
			if(tmpsym->func) 
				treefree(tmpsym->func);
			if(tmpsym->plist)
				listfree(tmpsym->plist);	
			free(tmpsym->name);
			break;
		}
		default:
			//printf("free error!\n");
			break;
	}

	free(past);
}

void listfree(param_st *plist) 
{
	param_st *pnext = NULL;

	if(plist != NULL) {
		while(plist != NULL) {
			pnext = plist->next;	
			free(plist);
			plist = pnext;
		}		
	}
}

int main(int argc, char *argv[])
{
	printf("> ");
	return yyparse();
}







