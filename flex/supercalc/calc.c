/**
 * \file calc.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月10日星期日10:32:38
 * 
 * discript your detail info.
 */ 
/**
 * the main frame.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <Jlog.h>

#include "calc.h"

/**
 * for hash computing
 */
static unsigned 
symhash(char *sym)
{
	unsigned int hash = 0;
	unsigned c;

	while((c = *sym++) != '\0') {
		hash = hash*9^c;	
	}

	return hash;
}

struct symbol *
lookup(char *sym)
{
	if(sym == NULL){
		dblog("the symbol is empty!\n");	
		return NULL;
	}	
	unsigned int hash = 0;
	struct symbol *result = NULL;
	int total = NHASH;

	hash = symhash(sym) % NHASH;
	result = &symtab[hash];
	while(total-- > 0) {
		if(result->name == NULL) {
			memset((char*)result, 0,sizeof(*result));
			result->name = strdup(sym);
			return result;
		} else if(!strcmp(result->name, sym)) {
			return result;	
		}	
			
		if(++result >= symtab+NHASH) {
			result = symtab;	
		}
	}

	yyerror("symbol table over flow!");
	abort();
	return 0;
}

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
	struct ast *past = NULL;

	past = (struct ast *)malloc(sizeof(struct ast));
	if(past == NULL) {
		dblog("alloc new ast failed!");	
		yyerror("out of space!");
		exit(0);
	}

	past->nodetype = nodetype;
	past->l = l;
	past->r = r;

	return past;
}

struct ast *newnum(double d)
{
	struct numval *pnewnum = NULL;

	pnewnum = (struct numval*) malloc(sizeof(struct numval));
	if(pnewnum == NULL) {
		dblog("alloc new numval failed!");	
		yyerror("out of space!");
		exit(0);
	}

	pnewnum->nodetype = 'K';
	pnewnum->number = d;

	return (struct ast *)pnewnum;
}

struct ast *newcmp(int functype, struct ast *l, struct ast *r)
{
	struct ast *pnewcmp = NULL;

	pnewcmp = (struct ast *)malloc(sizeof(struct ast));
	if(pnewcmp == NULL) {
		dblog("alloc new cmp failed!");	
		yyerror("out of space!");
		exit(0);
	}
	/* here we use the character 'zero' */
	pnewcmp->nodetype = '0' + functype;
	pnewcmp->l = l;
	pnewcmp->r = r;

	return pnewcmp;
}

struct ast *newfunc(int functype, struct ast *l)
{
	struct fncall *pcall = NULL;

	pcall = (struct fncall*) malloc(sizeof(struct fncall));
	if (pcall == NULL) {
		dblog("alloc new call failed!");	
		yyerror("out of space!");
		exit(0);
	}

	pcall->nodetype = 'F';
	pcall->l = l;
	pcall->functype = functype;

	return (struct ast *)pcall;
}

struct ast *newcall(struct symbol *s, struct ast *l)
{
	struct ufncall *pcall = NULL;

	pcall = (struct ufncall*)malloc(sizeof(struct ufncall));
	if(pcall == NULL) {
		dblog("alloc new fncall failed!");	
		yyerror("out of space!");
		exit(0);	
	}

	pcall->nodetype = 'C';
	pcall->l = l;
	pcall->s = s;

	return (struct ast*)pcall;
}

struct ast *newref(struct symbol *s)
{
	struct symref *pref = NULL;

	pref = (struct symref*)malloc(sizeof(struct symref));
	if(pref == NULL) {
		dblog("alloc new symref failed!");	
		yyerror("out of space!");
		exit(0);
	}

	pref->nodetype = 'N';
	pref->s = s;

	return (struct ast*)pref;
}

struct ast *newasgn(struct symbol *s, struct ast *v)
{
	struct symasgn *pasgn = NULL;

	pasgn = (struct symasgn*)malloc(sizeof(struct symasgn));
	if(pasgn == NULL) {
		dblog("alloc new symasgn failed!");	
		yyerror("out of space!");
		exit(0);
	}

	pasgn->nodetype = '=';
	pasgn->s = s;
	pasgn->v = v;
	
	return (struct ast*)pasgn;
}

struct ast *newflow(int nodetype, struct ast *cond, 
					struct ast *tl, struct ast *el)
{
	struct flow *pflow = NULL;

	pflow = (struct flow *)malloc(sizeof(struct ast));
	if(pflow == NULL) {
		dblog("alloc new flow failed!");	
		yyerror("out of space!");
		exit(0);
	}

	pflow->nodetype = nodetype;
	pflow->cond = cond;
	pflow->tl = tl;
	pflow->el = el;

	return (struct ast *)pflow;
}
/** 
 * \brief free the whole tree...
 * \note take care of the nodetype
 */
void treefree(struct ast *a)
{
	switch(a->nodetype) {
	/* two subtree */	
	case '+':
	case '-':
	case '/':
	case '*':
	case '1': case '2': case '3': case '4': case '5': case '6':
	case 'L':
		treefree(a->r);
	
	/* one subtree */
	case '|':
	case 'M': case 'C': case 'F':
		treefree(a->l);	
	
	/* no subtree */
	case 'K': case 'N':
		break;
	case '=':
		free(((struct symasgn *)a)->v);
		break;
	case 'I': case 'W':
		free(((struct flow *)a)->cond);
		if(((struct flow *)a)->tl) treefree(((struct flow *)a)->tl);
		if(((struct flow *)a)->el) treefree(((struct flow *)a)->el);
		break;
	default: 
		printf("internal eror: free bad node\n");
	}	

	free(a);
}

struct symlist *newsymlist(struct symbol *sym, struct symlist *next)
{
	struct symlist *psl = NULL;	

	psl = (struct symlist *)malloc(sizeof(struct symlist));
	if(psl == NULL) {
		dblog("alloc new symlist failed!");	
		yyerror("out of space");
		exit(0);
	}

	psl->sym = sym;
	psl->next = next;
	return psl;
}

void symlistfree(struct symlist *sl)
{
	struct symlist *nsl = NULL;

	while(sl) {
		nsl = sl->next;	
		free(sl);
		sl = nsl;
	}
}

/**
 * \brief  call build-in function
 */
static double callbuiltin(struct fncall *);

/**
 * \brief call user defined function
 */
static double calluser(struct ufncall *);

/**
 * \brief finall result;
 */
double 
eval(struct ast *a)
{
	double v = 0.0;

	if(a == NULL) {
		yyerror("internal error, null eval!");
		return 0.0;
	}
		
	switch(a->nodetype) {
		/* constant */
	case 'K':
		v = ((struct numval *)a)->number;
		break;
		/* name reference */	
	case 'N':
		v = ((struct symref *)a)->s->value;
		break;
	case '=': 
		v = ((struct symasgn *)a)->s->value =
		eval(((struct symasgn*)a)->v);
		break;
	/* expression */
	case '+': 
		v = eval(a->l) + eval(a->r); break;
	case '-':
		v = eval(a->l) - eval(a->r); break;
	case '*':
		v = eval(a->l) * eval(a->r); break;
	case '/':
		v = eval(a->l) / eval(a->r); break;
	case '|':
		v = fabs(eval(a->l)); break;
	case 'M':
		v = -eval(a->l); break;
	/* comparison*/	
	case '1':
		v = (eval(a->l) > eval(a->r))? 1: 0; break;	
	case '2':
		v = (eval(a->l) < eval(a->r))? 1: 0; break;
	case '3':
		v = (eval(a->l) != eval(a->r))? 1: 0; break;
	case '4':
		v = (eval(a->l) == eval(a->r))? 1: 0; break;
	case '5':
		v = (eval(a->l) >= eval(a->r))? 1: 0; break;
	case '6':
		v = (eval(a->l) <= eval(a->r))? 1: 0; break;
	
	case 'I':
		if(eval(((struct flow *)a)->cond) != 0) {
			if(((struct flow *)a)->tl) {
				v = eval(((struct flow *)a)->tl);	
			}	
		} else {
			if(((struct flow *)a)->el) {
				v = eval(((struct flow *)a)->el);	
			}	
		}	
		break;
		/* the while... */	
	case 'W':
		if (((struct flow *)a)->tl) {
			/* this while can go over? where does it store the status? */
			while(eval(((struct flow*)a)->cond) != 0) {
				v = eval(((struct flow *)a)->tl);	
			}	
		}
		break;
		/* list of statements */	
	case 'L':
		eval(a->l);
		v = eval(a->r);
		break;

	case 'F':
		v = callbuiltin((struct fncall*)a); break;
	case 'C':
		v = calluser((struct ufncall*)a); break;
	default	:
		printf("internal error: bad node! %c\n", a->nodetype);
	}

	return v;
}

/**
 * \brief call the built-in function
 */
static double
callbuiltin(struct fncall *f)
{
	enum bifs functype = f->functype;
	double v = eval(f->l);

	switch(functype) {
	case B_sqrt:
		return sqrt(v);
	case B_exp:
		return exp(v);
	case B_log:
		return log(v);
	case B_print:
		printf("= %4.4g\n", v);
		return v;
	default:
		yyerror("Unknown built-in function %d", functype);
	}

	return 0.0;
}

/**
 * \brief define a function
 */
void 
dodef(struct symbol *name, struct symlist *syms, struct ast *func)
{
	if(name->syms) 
		symlistfree(name->syms);

	if(name->func)
		treefree(name->func);
	
	name->syms = syms;
	name->func = func;
}
/**
 * \brief do the user call.
 */
static double
calluser(struct ufncall *f)
{
	struct symbol *fn = f->s;		/* function name */
	struct symlist *sl;				/* dummy arguments */
	struct ast *args = f->l;		/* actual arguments */
	double *oldval, *newval;		/* saved arg values */
	double v;
	int nargs;
	int i;

	if(fn->func == NULL) {
		yyerror("call to undefined function");	
		return 0;
	}
	/* count the arguments number */
	sl = fn->syms; 
	for(nargs = 0; sl; sl = sl->next) 
		nargs++;
	
	oldval = (double *)malloc(sizeof(double) * nargs);
	newval = (double *)malloc(sizeof(double) * nargs);
	if(oldval == NULL || newval == NULL) {
		yyerror("Out of space!");
		return 0.0;
	}

	/* evalueate the arguments */
	for(i = 0; i < nargs; i++) {
		if(args == NULL) {
			yyerror("too few args in call to %s", fn->name);	
			free(oldval);
			free(newval);
			return 0.0;
		}	

		if(args->nodetype == 'L') {
			newval[i] = eval(args->l);	
			args = args->r;
		} else {
			newval[i] = eval(args);	
			args = NULL;
		}
	}

	/* save old values of dummies, assign new ones */
	sl = fn->syms;
	for(i = 0; i < nargs; i++) {
		struct symbol *s = sl->sym;	

		oldval[i] = s->value;
		s->value = newval[i];
		sl = sl->next;
	}

	free(newval);
	/* call the user function */	
	v = eval(fn->func);
	
	/* put the dummies back */
	sl = fn->syms;
	for(i = 0; i < nargs; i++) {
		struct symbol *s = sl->sym;	

		s->value = oldval[i];
		sl = sl->next;
	}

	free(oldval);

	return v;
}

void yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	va_end(ap);

	fprintf(stderr, "\n");
}


int main(int argc, char *argv[])
{
	printf("> ");
	return yyparse();
}

