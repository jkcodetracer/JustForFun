#include <stdio.h>
#include <string.h>


int main()
{
	char line[1024];
		
	while(fgets(line, 1024, stdin) != NULL)
	{
		printf("%d:::%d::\n", strcspn(line, "asdf,"), strspn(line, "asdf,"));
	}
	return 0;
}
