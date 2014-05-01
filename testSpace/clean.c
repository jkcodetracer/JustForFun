#include <stdio.h>

void define_array()
{
	int array[5];
	int i;

	for(i = 0; i <= 4;  i++) {
		array[i] = i;	
	}
}

void print_array()
{
	int array[5];
	int i;

	for (i = 0; i <= 4; i++) {
		printf ("%d\n", array[i]);	
	}
}
	
int main()
{
	define_array();
	print_array();
}

