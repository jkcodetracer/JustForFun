/**
 * \file wc.l
 * \author  wzj
 * \brief 
 	for wc... a simple flex deamon
 * \version 
 * \note  
 * \date: 2013年01月01日星期二10:16:16
 * 
 * discript your detail info.
 */ 

/* decleration */
%{
	int chars = 0;
	int words = 0;
	int lines = 0;

	int totalchr 	= 0;
	int totalwords 	= 0;
	int totallines 	= 0;
%}

/* rules */
/* [a-zA-Z]+	{words++; chars += strlen(yytext);}	 */

%%
[^ \t\n\r\f\v]+		{words++; chars += strlen(yytext);}	
\n					{chars++; lines++;}
.					{chars++;}
%%

int main(int argc, char *argv[])
{
	int i = 0;
	/* input... */
	for(i = 1; i < argc; i++) {
		FILE *f = fopen(argv[i], "r");	
		if(f == NULL) {
			printf("open [%s] failed!\n", argv[i]);
			continue;	
		}
		yyrestart(f);
		yylex();
		fclose(f);
		printf("lines:[%8d] words:[%8d] chars:[%8d] file:[%s]\n", lines, words, chars, argv[i]);
		totalchr 	+= chars, chars = 0;
		totalwords 	+= words, words = 0;
		totallines 	+= lines, lines = 0;
	}

	printf("lines:[%8d] words:[%8d] chars:[%8d] :total\n", totallines, totalwords, totalchr);

	return 0;
}


