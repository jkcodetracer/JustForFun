#include <stdio.h>

void foo()
{
	int test[4];
	int i = 0;

	for (i = 0; i <=4; i++) {
		printf ("%d\n", i);
		test[i] -=4;
	}
}

int main()
{
	int i = 0;

	printf ("%p\n", &i);
	i++;
	//foo();
}
