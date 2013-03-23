/**
 * \file lineno.l
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年01月06日星期日21:22:45
 * 
 * discript your detail info.
 */ 
/* don't use the default yywrap, to swap the file. */
%option noyywrap
%x IFILE

%{
	struct bufstack {
		struct bufstack *prev;	
		YY_BUFFER_STATE bs;
		int lineno;
		char *filename;
		FILE *f;
	} *curbs = NULL;

	char *curfilename;

	int newfile(char *fn);
	int popfile(void);
%}

%%

^"#"[ \t]*include[ \t]*\[\"<] 	{BEGIN IFILE;} 		/* trail context, the reg after the "\" must be matched! */
<IFILE>[^ \t\n\">]+				{
									{
										int c;
										while((c = input()) && c != '\n')
											;
									}
									yylineno++;
									if(!newfile(yytext))
										yyterminate();
									BEGIN INITIAL;		/* turn to the beginning status. */
								}

<IFILE>.|\n						{
									fprintf(stderr, "%4d bad include line\n", yylineno);
									yyterminate();
								}
<<EOF>>							{ if(!popfile()) yyterminate();}
^.								{ fprintf(yyout, "%4d %s", yylineno, yytext);}
^\n								{ fprintf(yyout, "%4d %s", yylineno++, yytext);}
\n								{ ECHO; yylineno++;}
.								{ ECHO;}


%%


int main(int argc, char *argv[])
{
	if(argc < 1) {
		perror("invalid input");
		return -1;	
	}

	if(newfile(argv[1]))
		yylex();
	
	return 0;
}

int newfile(char *fn)
{
	FILE *f = fopen(fn, "r");
	if(f == NULL) {
		perror(fn);	
		return 0;
	}
	
	struct bufstack *bs = malloc(sizeof(struct bufstack));
	if(bs == NULL) {
		perror("malloc bs failed!");	
		fclose(f);
		return 0;
	}

	if(curbs)
		curbs->lineno = yylineno;
	bs->prev = curbs;
	/*set up current entry */
	bs->bs 	= yy_create_buffer(f, YY_BUF_SIZE);
	bs->f	= f; 
	bs->filename = fn;
	
	yy_switch_to_buffer(bs->bs);
	curbs 	= bs;
	yylineno = 1;
	curfilename = fn;
	
	return 1;
}


int popfile(void)
{
	struct bufstack *bs = curbs;
	struct bufstack *prevbs;

	if(!bs)
		return 0;

	fclose(bs->f);
	yy_delete_buffer(bs->bs);
	
	prevbs = bs->prev;
	free(bs);

	if(!prevbs)
		return 0;
	
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	return 1;
}



