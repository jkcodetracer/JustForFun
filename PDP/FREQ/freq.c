#include <stdio.h>
#include <ctype.h>
#include <limits.h>

unsigned long count[UCHAR_MAX + 1] = {0};

int main(int argc, char** argv)
{
	int c = EOF;
	int i = 0;

	while((c = getchar()) != EOF)
		count[c] ++;

	for(i = 0; i < UCHAR_MAX; i++)
	{
		if (count[i] != 0)
		{
			printf("%.2x, %c %lu\n",
					i, isprint(i) ? i : '-', count[i]);
		}	
	}

	return 0;

}
