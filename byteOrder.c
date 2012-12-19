/*
 * @FileName: byteOrder
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
 * @Date: 2011年12月06日星期二22:13:52
 * 
 */ 
#include<stdio.h>

int main()
{
	char test[] = {'192','168','39','10'};
	unsigned int mybyte=(unsigned int)test;

	printf("%x\n", mybyte);

	return 0;
}
