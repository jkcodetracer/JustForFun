#include <stdio.h>
#include <stdlib.h>

int test_int(char *p, int size)
{
	if(size - sizeof(int) >= 0)
		printf("over flow!!!\n");
	
	return size;
}

int main(int argc, char *argv[])
{
	test_int("123", 3);

	return 0;
}
