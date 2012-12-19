#include <stdio.h>
#include <stdlib.h>


int main()
{
	char *ptr = NULL;
	long size = 1024*1024*5;
	long long i = 0;

	while(1)
	{
		char *tmpptr = NULL;
		tmpptr = (char*) realloc(ptr, i*size);
		if(tmpptr == NULL)
		{
			printf("ptr: %lld\n", i*5);
			break;
		}

		ptr = tmpptr;
		i++;
		usleep(10);
	}

	return 0;
}
