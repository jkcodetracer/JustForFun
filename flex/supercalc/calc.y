/**
 * \file calc.y
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月09日星期六23:03:24
 * 
 * discript your detail info.
 */ 
%{
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
%}

/* put all the symbol into the union, for the inner use. */
%union{
	struct ast *a;
	double d;
	struct symbol *s;
	struct symlist *sl;
	int fn;
}

%token <d>	NUMBER
%token <s> 	NAME 
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO LET

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

/* declare the beginning status. */
%start calclist 

%%
/* flow control */
stmt: IF exp THEN list 			{$$ = newflow('I', $2, $4, NULL);}
| IF exp THEN list ELSE list 	{$$ = newflow('I', $2, $4, $6);}
| WHILE exp DO list				{$$ = newflow('W', $2, $4, NULL);}
| exp
;

/* to solve the recursive flow control */
list: 		{$$ = NULL;}
| stmt ';' list {
	if ($3 == NULL)	
		$$ = $1;
	else 
		$$ = newast('L', $1, $3);
}
;

/* the calculators */
exp: exp CMP exp 				{$$ = newcmp($2, $1, $3);}
| exp '+' exp					{$$ = newast('+', $1, $3);}
| exp '-' exp 					{$$ = newast('-', $1, $3);}
| exp '*' exp					{$$ = newast('*', $1, $3);}
| exp '/' exp					{$$ = newast('/', $1, $3);}
| '|' exp						{$$ = newast('|', $2, NULL);}
| '(' exp ')'					{$$ = $2;} 
| '-' exp %prec UMINUS			{$$ = newast('M', $2, NULL);}
| NUMBER						{$$ = newnum($1);}
| NAME							{$$ = newref($1);}
| NAME '=' exp					{$$ = newasgn($1, $3);}
| FUNC '(' explist ')'			{$$ = newfunc($1, $3);}
| NAME '(' explist ')'			{$$ = newcall($1, $3);}
;
/* deal the param like the C stack */
explist: exp
| exp ',' explist {$$ = newast('L', $1, $3);}
;
symlist: NAME 					{$$ = newsymlist($1, NULL);}
| NAME ',' symlist 				{$$ = newsymlist($1, $3);}
;

calclist:
| calclist stmt EOL {
	printf("= %4.4g\n>", eval($2));
	treefree($2);
}
/* this defination support function call when define a function. */
| calclist LET NAME '(' symlist ')' '=' list EOL{
	dodef($3, $5, $8);
	printf("Defined %s\n>", $3->name);
}
| calclist error EOL {yyerror; printf("> ");}
;

%%
