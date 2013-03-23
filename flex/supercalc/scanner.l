/**
 * \file scanner.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年03月10日星期日09:28:21
 * 
 * discript your detail info.
 */ 
%option noyywrap nodefault yylineno

%{
#include "calc.h"
#include "calc.tab.h"
%}

EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")" 	{return yytext[0];}

 /* compare ops. */
">" 	{yylval.fn = 1; return CMP;}
"<" 	{yylval.fn = 2; return CMP;}
"!="	{yylval.fn = 3; return CMP;}
"<>" 	{yylval.fn = 3; return CMP;}
"==" 	{yylval.fn = 4; return CMP;}
">=" 	{yylval.fn = 5; return CMP;}
"<="	{yylval.fn = 6; return CMP;}

 /* keywords */
"if"	{return IF;}
"then" 	{return THEN;}
"else" 	{return ELSE;}
"while"	{return WHILE;}
"do"	{return DO;}
"let"	{return LET;}

 /* build in function */
"sqrt"	{yylval.fn = B_sqrt; return FUNC;}
"exp"	{yylval.fn = B_exp; return FUNC;}
"log"	{yylval.fn = B_log; return FUNC;}
"print"	{yylval.fn = B_print; return FUNC;}

 /* names */
[a-zA-Z][a-zA-Z0-9]*	{yylval.s = lookup(yytext); return NAME;}

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? 		{yylval.d = atof(yytext); return NUMBER;}

"//".*
[ \t] 		/* ignore the white space. */

\\\n	{printf("c> ");}		/* ignore line continuation. */

\n		{return EOL;}

.		{yyerror("Mystery character %c\n", *yytext);}

%%


