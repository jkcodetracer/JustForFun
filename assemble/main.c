/*
 * @FileName: main.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月31日星期四23:51:34
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>

struct tes{
	int a;
	int b;
};

int plus(char op, char base, struct tes ct,int a, int b)
{
	int c = 2;
	int d = 3;
	int e = 4;
	char o = 'a';

	if(op == 'a')
	{
		char *ff = "codetracer";
		*ff = 'k';
		return a+b;
	}

	return base;
}

int main()
{
	int a = 1;
	int b = 14;
	struct tes ct = {13, 45};

	printf("plus:%d\n", plus('a', 'd', ct,a, b));
}
