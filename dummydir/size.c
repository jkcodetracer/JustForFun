#include <stdio.h>


int main(int argc, char *argv[])
{
	const char test[][10] = {
		"aaaaa", "bbbb", "cccc", "ddeed"	
		};
	
	printf("sizeof [%d]\n", sizeof(test));

	return 0;
}
