calc_super: scanner.l calc.y calc.h
	bison -d calc.y
	flex -o scanner.lex.c scanner.l
	gcc -o $@ calc.c scanner.lex.c calc.tab.c -lm

.PHONY: clean

clean:
	rm -f calc.tab.c calc_super scanner.lex.c 
