#include <stdio.h>

int main()
{
	printf("%f\n%d\n", sizeof('a')+ 0.1 + sizeof('b'), sizeof("a"));
	return 0;
}
