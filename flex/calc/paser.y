/**
 * \file paser.y
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月01日星期二15:46:24
 * 
 * discript your detail info.
 */ 

%{
#include <stdio.h>
%}

/* tokens */
%token NUMBER HEX CP OP
%token ADD MINUS TIME DIV ABS UPP
%token EOL

%%

callist: 
| callist exp EOL{printf(" = %d\n", $2);}
;

exp: factor	
| exp ADD factor {$$ = $1 + $3;}
| exp MINUS factor {$$ = $1 - $3;}
;

factor: upper
| factor TIME upper {$$ = $1 * $3;}
| factor DIV upper {$$ = $1 / $3;}
;

upper: term
| upper UPP term {int i;$$ = 1; for(i = 0; i < $3; i++) { $$ = $$ * $1;}} 
;

term: num
| ABS term {$$ = $2 >= 0? $2: -$2;}
| CP exp OP {$$ = $2;}
| MINUS term {$$ = -$2;}
;

num: NUMBER
| HEX 
;

%%

int main(int argc, char *argv[])
{
	yyparse();
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}

