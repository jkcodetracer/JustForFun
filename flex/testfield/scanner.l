/**
 * \file scanner.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月12日星期二23:29:35
 * 
 * discript your detail info.
 */ 

%option noyywrap nodefault yylineno

%{
#include <stdio.h>
#include <stdlib.h>

#include "calc.tab.h"
#include "calc.h"
%}

%%
";" |
"," |
"+" |
"-" |
"*" |
"/" | 
"=" |
"(" |
")"  	{return yytext[0];}

"let" 	{return LET;}

[a-zA-Z][a-zA-Z0-9]*	{yylval.name = lookup(yytext); return NAME;}

[0-9]+"."[0-9]* |
"."?[0-9]+ {yylval.d = atof(yytext); return NUMBER;}

"//".*
[ \t] 	/* ignore the space */

\\\n 	{printf("c> ");}

\n		{return EOL;} 

.		{printf("Mystery character %c\n", *yytext);}

%%


