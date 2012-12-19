#include "csv.h"
#include <unistd.h>
#include <stdio.h>

int main()
{
	int i ;

	char *line;

	while((line = csvgetline(stdin)) != NULL)
	{
		printf("%s\n", line);
		for (i = 0 ; i < csvgetnfeild(); i++)
		{
			printf("field[%d]: %s\n", i, csvgetfeild(i));
		}
	}

	return 0;
}
