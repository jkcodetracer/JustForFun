## put the paser.tab.h into the scaner.l
calc: scanner.l paser.y
	bison -d paser.y
	flex scanner.l
	gcc -o $@ paser.tab.c lex.yy.c -lfl
