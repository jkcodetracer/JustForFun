/*
 * @FileName: static_val.c
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
 * @Date: 2012年06月17日星期日18:26:04
 * 
 */ 
#include <stdio.h>

//int g_val_init = 45;
//int g_val_uninit;
static int s_global_inited = 12;
static int s_global_uninited;

struct ct_type{
	char st_s_val;
	char st_val;
};

int 
foo()
{
	static int s_foo_init = 67;
	static int s_foo_uninited;

	printf("hello..\n");
	return 0;
}

int main()
{
	static int s_local_inited = 23;
	static int s_local_uninited;
	static struct ct_type s_ct = {.st_s_val=133, .st_val=132 };
	struct ct_type local_ct;
	int tmp = 100;

	printf("%d..\n", tmp);	
	return 0;
}
