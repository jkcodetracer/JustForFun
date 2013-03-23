/**
 * \file parser.y
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月02日星期三22:40:25
 * 
 * discript your detail info.
 */ 

%{
#include <stdio.h>
%}

%token LEFTQUOT RIGHTQUOT EQUAL 
%token TOKEN

%%
inilist:
| inilist exp {}
;

exp:
| LEFTQUOT TOKEN RIGHTQUOT {printf("%s\n", yylval);}
;

%%

