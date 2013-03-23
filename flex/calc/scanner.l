/**
 * \file paser.l
 * \author  wzj
 * \brief 
 v0.1. simple recognize and print.
 v0.2. user the coroutine to get the value, one by one. 
 * \version 
 * \note  
 * \date: 2013年01月01日星期二13:32:31
 * 
 * discript your detail info.
 */ 
%{
#include "paser.tab.h"
/*	enum yytokentype {
		NUMBER 	= 267,
		ADD 	= 268,	
		MINUS	= 269,
		TIME	= 270,
		DIV		= 271,
		ABS		= 272,
		EOL		= 273
	};

	int yyval;
*/
%}

%%
"+" 	{return ADD;}
"-" 	{return MINUS;}
"*" 	{return TIME;}
"/" 	{return DIV;}
"|"		{return ABS;}
"("		{return CP;}
")"		{return OP;}
"^"		{return UPP;}
0(x|X)[a-fA-F0-9]+	{yylval = strtol(yytext + 2/* 0x.. */, NULL, 16); return HEX;}
[0-9]+	{yylval = atoi(yytext);return NUMBER;}
[ \t]	{ }
\n		{return EOL;}
.		{printf("Invalid char: %c\n", *yytext);}
%%
/*
int main(int argc, char *argv[])
{
	int tok;

	while(tok = yylex()) {
		printf("%d", tok);	
		if(tok == NUMBER) 
			printf(" = %d\n", yyval);
		else
			printf("\n");
	}
}
*/


