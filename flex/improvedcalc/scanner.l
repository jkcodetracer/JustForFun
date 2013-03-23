/**
 * \file scanner.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月02日星期六23:58:25
 * 
 * discript your detail info.
 */ 

%option noyywrap nodefault yylineno

%{
#include "calc_head.h"
#include "calc_head.tab.h"
%}

/* as the macro, for the float number */
EXP ([Ee][-+]?[0-9]+)

%%
"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" 	{return yytext[0];}
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? {yylval.d = atof(yytext); return NUMBER;}

\n 		{return EOL;}
"//".*
[ \t] 	{/* ignore whitespace */}
.		{yyerror("Mystery character %c\n", *yytext);}

%%


