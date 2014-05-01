/**
 * \file calc.y
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月12日星期二23:37:35
 * 
 * discript your detail info.
 */ 
%{
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
%}

%union{
	struct _ast_st	*a;
	struct _symbol_st *name;
	struct _param_st *param;
	int	t;
	char * c;
	double 	d;
}

%token <name>	NAME
%token <d> 		NUMBER
%token <t> 		CMP
%token EOL
%token LET

%nonassoc CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <a> exp list explist
%type <param> paramlist

%start calclist 

%%
calclist: 
| calclist exp EOL {
	printf("%4.4g\n> ",eval($2));
	treefree($2);
	}
| calclist error EOL {
	printf("> ");
}
| calclist LET NAME '(' paramlist ')' '=' list EOL {
	dodef($3, $5, $8);
	printf("defined :[%s]\n> ", $3->name);
}
;

exp: '-' exp %prec NMINUS 	{$$ = newast('M', $2, NULL);}
| exp '+' exp				{$$ = newast('+', $1, $3);}
| exp '-' exp				{$$ = newast('-', $1, $3);}
| exp '*' exp				{$$ = newast('*', $1, $3);}
| exp '/' exp				{$$ = newast('/', $1, $3);}
| exp CMP exp				{$$ = newcmp($2, $1, $3);}
| '(' exp ')' 				{$$ = $2;}
| NUMBER					{$$ = newnum($1);}
| NAME						{$$ = newname($1);}
| NAME '(' explist ')'		{$$ = newcall($1, $3);}
;

explist: exp				
| exp ',' explist 			{$$ = newast('L', $1, $3);}
;

paramlist: NAME		 		{$$ = newsymlist($1, NULL);}
| NAME ',' paramlist 		{$$ = newsymlist($1, $3);}
;

list:		{$$ = NULL;}
| exp ';' list {
			if($3 == NULL)
				$$ = $1;
			else
				$$ = newast('L', $1, $3);
			}
;
%%




