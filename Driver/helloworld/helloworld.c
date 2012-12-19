/*
 * @FileName: helloworld.c
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
 * @Date: 2012年07月25日星期三21:29:47
 * 
 */ 
#include <linux/init.h>		//init and exit
#include <linux/module.h>	//modules must own
#include <linux/moduleparam.h>	//for module_param
#include <linux/stat.h>		//for S_IRUSR

#define HELLO_ARRAY_SIZE	(32)

int test;
//this param is better to defined as the static one
int array[HELLO_ARRAY_SIZE] = {0};
int n;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("code_tracer");
//MODULE_PARM(var, type) type could be b:byte h:short i:int l:long s:string
//MODULE_PARM(test, "i"); this function is in 2.4.xxx 
//module_param(test, int, S_IRUSR);
module_param(test, int, S_IRUSR);
module_param_array(array, int, &n, S_IRUGO);

static int
__init hello_init(void)
{
	int i = 0;

	printk("hello world! %d\n", test);
	for(i = 0; i < HELLO_ARRAY_SIZE; i++)
	{
		printk("...%d...\n", array[i]);
	}
	return 0;
}

static void
__exit hello_exit(void)
{
	printk("goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

