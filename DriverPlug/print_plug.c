/**
 * \file print_plug.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月26日星期日20:07:37
 */ 

#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");


typedef void* (*plug_func_t)(int, int);

typedef struct _plug_st{
	plug_func_t pfunc;
	struct _plug_st *next;
}plug_st;

extern int plug_regist(plug_st *pplug);

void *print_hello(int a, int b)
{
	printk("hello world! I'm plug.\n");
	return NULL;
}

plug_st my_plug;

static int __init print_init(void)
{
	my_plug.pfunc = print_hello;
	my_plug.next = NULL;

	printk("init print plug\n");
	plug_regist(&my_plug);

	return 0;
}

static void __exit print_exit(void)
{
	printk("print_ register exit!\n");	
}

module_init(print_init);
module_exit(print_exit);

