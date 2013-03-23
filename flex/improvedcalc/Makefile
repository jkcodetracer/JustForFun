calc_imp: scanner.l calc_head.y calc_head.h
	bison -d calc_head.y
	flex -o scanner.lex.c scanner.l
	gcc -o $@ calc_main.c scanner.lex.c calc_head.tab.c

.PHONY: clean

clean:
	rm -f calc_head.tab.c calc_imp scanner.lex.c 
