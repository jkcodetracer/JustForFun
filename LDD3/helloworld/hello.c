/*
 * @FileName: hello.c
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
 * @Date: 2012年02月16日星期四00:28:52
 * 
 */ 
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT"hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT"goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
