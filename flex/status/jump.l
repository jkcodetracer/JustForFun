/**
 * \file jump.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月06日星期日22:56:40
 * 
 * discript your detail info.
 */ 

%option noyywrap
%x YA
%x YB
%x ONE
%x TWO
%x THREE
%x KEY
%x VALUE
%x SECTION
%x LT
%x RT

%{
	int i = 0;
%}

%%

"1" {BEGIN ONE;printf("%d\n", 1);}
<ONE>"one" {BEGIN TWO; printf("%d\n", 2);}
<TWO>"two" {BEGIN THREE; printf("%d\n", 3);}
<THREE>"three" {BEGIN INITIAL; printf("init..\n");}
"4" {BEGIN YA; printf("ya\n");}
<YA>"5" {BEGIN YB; printf("yb\n");}
<YB>"6" {BEGIN INITIAL; printf("y over\n");}

[2]{1,1} {printf("no2\n");}
[3]{1,1} {printf("no3\n");}

"[" {BEGIN SECTION;}
<SECTION>[^ \t\n\"\]]+ {BEGIN KEY; printf("tag:[%s]\n", yytext);}
<KEY>[^ \t\n\"\]=\[]+		{BEGIN VALUE; printf("key:[%s]\n", yytext);}
<KEY>"[" 	{BEGIN INITIAL;}
<VALUE>[ \t]*[a-zA-Z]+ {BEGIN KEY; printf("value:[%s]\n", yytext);}

%%

int main()
{
	yylex();
	return 0;
}

