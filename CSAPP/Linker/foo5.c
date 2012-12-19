/*
 * @FileName: foo5.c
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
 * @Date: 2012年04月22日星期日08:39:30
 * 
 */ 
#include <stdio.h>

void f(void);

int x = 15434; //被覆盖了
int y = 15666; //被覆盖了

int main()
{
	f();
	printf("x = 0x%x y = 0x%x \n", x, y);

	return 0;
}
