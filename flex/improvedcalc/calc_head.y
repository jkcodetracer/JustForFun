/**
 * \file calc_head.y
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月03日星期日16:47:43
 * 
 * discript your detail info.
 */ 
%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <Jlog.h>

#include "calc_head.h"
%}

%union{
	struct ast *a;
	double d;
}

/* define the precedence and the associativity */
%left '+' '-'	/* left associativity, level3 */
%left '*' '/'	/* left associativity, level2 */
%nonassoc '|' UMINUS /* single... level1,  the UMINUS is for '-' */

%token <d> NUMBER
%token EOL

%type <a> exp

%%
calclist:
| calclist exp EOL{
	printf("= %4.4g\n", eval($2));	
	treefree($2);
	printf("> ");
}
| calclist EOL{
	printf("> ");
};

exp: exp '+' exp {$$ = newast('+', $1, $3);}
| exp '-' exp {$$ = newast('-', $1, $3);}
| exp '*' exp {$$ = newast('*', $1, $3);}
| exp '/' exp {$$ = newast('/', $1, $3);}
| '|' exp 	  {$$ = newast('|', $2, NULL);}
| '(' exp ')' {$$ = $2;}
| '-' exp %prec UMINUS {$$ = newast('M', $2, NULL);}
| NUMBER	  {$$ = newnum($1);}
;

%%





