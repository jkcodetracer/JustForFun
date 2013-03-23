/**
 * \file calc_head.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年02月27日星期三21:12:53
 * 
 * discript your detail info.
 */ 

extern int yylineno;
void yyerror(char *s, ...);

/* for the abstract syntax tree */
struct ast{
	int nodetype;
	struct ast *l;
	struct ast *r;
};

struct numval{
	int nodetype;
	double number;
};

/** 
 * \brief ast generator 
 */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);

/**
 * \brief evaluate an ast
 * \note get the final result;
 */
double eval(struct ast *);

/**
 * \brief: delete and free an AST
 */
void treefree(struct ast *);





