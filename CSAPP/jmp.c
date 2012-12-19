/*
 * @FileName: jmp.c
 * @Author: wzj
 * @Brief: 
 * 1.setjmp/longjmp easy simple. 
 * 2.只跳转一次，不需要解开嵌套的堆栈。 
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月02日星期三07:07:13
 * 
 */ 
#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;

int error1 = 0;
int error2 = 1;

void foo(void);
void bar(void);

int 
main()
{
	int rc;
	rc = setjmp(buf);
	if(rc == 0)
		foo();
	else if (rc == 1)
		printf("Detected an error1 condition in foo\n");
	else if (rc == 2)
		printf("Detected an error2 condition in foo\n");
	else 
		printf("Unknown error condition in foo\n");
	
	exit(0);
}

void 
foo(void)
{
	if(error1)
		longjmp(buf, 0); //返回值被rc接住，但是不会返回0， 返回你在
						//第二个参数设定的值，或者1。
	bar();
}

void bar(void)
{
	if(error2)
		longjmp(buf, 0);
}
