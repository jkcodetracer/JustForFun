/**
 * \file calc.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月12日星期二23:00:33
 * 
 * discript your detail info.
 */ 

#ifndef _CALC_H
#define _CALC_H

extern int yylineno;
void yyerror(char *s, ...);
/* the base element, used to build the grammar tree. */
typedef struct _ast_st{
	int nodetype;
	struct _ast_st *l;
	struct _ast_st *r;
}ast_st;

/**
 * \the number kind
 */
typedef struct _num_st{
	int nodetype;			/* type N, the number */
	double number;
}num_st;
/**
 * \brief for the symbol in the ground
 */
typedef struct _symbol_st{
	char *name;				/* a symbol must have a name. */
	double value;			/* for function, a symbol may have a real value. */
	ast_st *func;			/* for function, the function is a grammar tree! */
	struct _param_st *plist;		/* for function, the function's params list. */
}symbol_st;

/**
 * \brief the param list
 */
typedef struct _param_st{
	symbol_st *sym;			/* the symbol it point to */
	struct _param_st *next;	/* use it to form a list. */
}param_st;

/* the function type. */
typedef struct _ufunc_st{
	int nodetype;			/* type U, the function */
	symbol_st *func;		/* the function */
}ufunc_st;
/* the call struct */
typedef struct _cfunc_st{
	int nodetype;			/* type C, call the function */
	symbol_st *func;		/* the function will be called */
	ast_st *plist;		/* the real param list */
}cfunc_st;

/* the param for function */
typedef struct _name_st{
	int nodetype;			/* type S, the param */
	symbol_st *sym;			/* it's content. */
}name_st;

/* the compare caculer */
typedef struct _cmp_st{
	int nodetype;			/* type '0' '1' ...*/
	ast_st *l;				
	ast_st *r;
}cmp_st;

#define NHASH	(9999)

symbol_st symbol_table[NHASH];

symbol_st *lookup(char* name);
ast_st *newast(int type, ast_st *l, ast_st *r);
ast_st *newnum(double d);
ast_st *newcmp(int type, ast_st *l, ast_st *r);
//ast_st *new_userfunc(ast_st *func, param_st *plist);
//ast_st *new_callfunc(symbol_st *func, param_st *plist);
ast_st *newname(symbol_st *name);
ast_st *newsymlist(symbol_st *name, param_st *pparam);
ast_st *newcall(symbol_st *name, ast_st *plist);


void dodef(symbol_st *name, param_st *plist, ast_st *func);
double eval(ast_st *past);
void treefree(ast_st *past);

#endif

