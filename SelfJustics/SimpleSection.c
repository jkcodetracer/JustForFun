/*
 * @FileName: SimpleSection.c
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
 * @Date: 2012年06月06日星期三23:06:58
 * 
 */ 
int 
printf(const char *format, ...);

int global_init_var = 84;
int global_uninit_var;

void func1(int i)
{
	printf("%d\n", i);
}

int
main()
{
	static int static_var = 85;
	static int static_var2;
	int a = 1;
	int b;

	func1(static_var + static_var2 + a + b);
	return a;
}


