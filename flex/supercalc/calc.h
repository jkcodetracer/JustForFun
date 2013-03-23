/**
 * \file calc.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月09日星期六21:27:55
 * 
 * discript your detail info.
 */ 

extern int yylineno;	/* for lexer */
void yyerror(char *s,...);

/* for the defined function */
/* this is a hash table */
struct symbol{
	char *name;				/* the function's name */
	double value;			/* ... */
	struct ast *func;
	struct symlist *syms;
};

#define NHASH	(9997)
struct symbol symtab[NHASH];
/**
 * \brief search the symtable.
 */
struct symbol *lookup(char*);

/**
 * the arguments, it's also a symbol.
 */
struct symlist {
	struct symbol *sym;
	struct symlist *next;
};

/**
 * \brief put all the symbols together.
 */
struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/**
 * \brief all the nodes struct below has a member "nodetype".
 * 		This is just like the turing machines's status, isn't it?
 *		And what's more, because of the flow control operations, 
 *		this simple calculator is Turing Complete!
 * 		What a show!
 */

/**
 * type L expression or statement list
 * type S list of symbols 
 * type M unary minus
 */

/**
 * \brief the build-in function.
 */
enum bifs{
	B_sqrt = 1,
	B_exp,
	B_log,
	B_print
};

/** 
 * \brief for the grammar tree.
 */
struct ast{
	int nodetype;
	struct ast *l;
	struct ast *r;
};

/**
 * \brief the build-in function
 */
struct fncall{
	int nodetype;			/* type F */
	struct ast *l;
	enum bifs functype;
};

/**
 * \brief user function
 */
struct ufncall{
	int nodetype;			/* type C */
	struct ast *l;			/* list of arguments */
	struct symbol *s;
};

/**
 * \brief this is for the flow ctrl: 
 * 		1. if xx else xx   	as the type I
 * 		2. while xx do xx	as the type W
 */
/* this struct seems like firmed! but as a kind of
 language, this two kinds of flow ctrl is enough.
 */
struct flow{
	int nodetype;			/* type I or W */
	struct ast *cond;		/* condition */
	struct ast *tl;			/* then branch or do list */
	struct ast *el;			/* else branch */
};

/**
 * \brief for a numbers...
 */
struct numval{
	int nodetype;			/* type K */
	double number;			/* the real numbers */
};

/**
 * \brief symbol reference.
 */
struct symref{
	int nodetype;			/* type N */
	struct symbol *s;
};

/**
 * \brief ...assigment, for the final/middle result.
 */
struct symasgn{
	int nodetype;			/* type = */
	struct symbol *s;		
	struct ast *v;			/* value */
};

/* to build the back born of the system */
/* to define a kind of AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el);

/* define a  */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
double eval(struct ast *);

/* delete and free an ast. */
void treefree(struct ast *);





