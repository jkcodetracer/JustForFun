#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int step_print(int i)
{
	return i;
}

int stepback(int n)
{
	int k = 100;
	int m = 455;
	int j = 134;
	int i = 0;
	
	if(n < 10000000000)
		return stepback(n+1);

	return step_print(i);	
}


int main(int argc, char *argv[])
{
	int ret = 0;

	ret = stepback(0);
	printf("%d\n", ret);
	
	return 0;
}
