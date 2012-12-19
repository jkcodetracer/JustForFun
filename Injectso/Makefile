OBJ=gptrace.o gelf.o

all: injectso-finder
injectso-finder: injectso-finder.c $(OBJ)
	gcc -O2 $< -o $@ -Wall $(OBJ)
gptrace.o: gptrace.c
	gcc -O2 $< -c -o $@ -Wall
gelf.o: gelf.c
	gcc -O2 $< -c -o $@ -Wall
clean:
	rm *.o -rf
	rm injectso-finder -rf 

