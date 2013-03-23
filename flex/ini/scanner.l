/**
 * \file scanner.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月02日星期三22:19:59
 * 
 * discript your detail info.
 */ 

%{
#include <stdio.h>
	enum types{
		TOKEN = 256,
		EQUAL = 258,
		LEFTQUOT = 259,
		RIGHTQUOT = 260
	};
%}

%%
"="				{printf("=\n"); return EQUAL;}
"["				{printf("[\n"); return LEFTQUOT;}
"]"				{printf("]\n"); return RIGHTQUOT;}
[^=\[ \]\t\r\n\v\f]+ {printf("%s\n", yytext);return TOKEN;}
[ \t\r]			{ }
%%

int main(int argc, char *argv[])
{
	int tok;

	while(tok = yylex()) {
			
	}
}


