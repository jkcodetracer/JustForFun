#include <stdio.h>
#include <stdlib.h>

int
main()
{
	char *myenv;

	myenv = getenv("SHELL");
	printf("myenv: %s   %p\n", myenv, myenv);
	return 0;
}
