/**
 * \file base.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月26日星期日16:44:48
 */ 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");

#define MAJOR_NUM 	(239)

static ssize_t plug_base_read(struct file*, char *, size_t, loff_t*);
static ssize_t plug_base_write(struct file*, const char *, size_t, loff_t*);
static int plug_base_open(struct inode *inode, struct file *filp);
static int plug_base_release(struct inode *inode, struct file *filp);

static int plug_walk(void);

typedef void* (*plug_func_t)(int, int);

typedef struct _plug_st{
	plug_func_t pfunc;	
	struct _plug_st *next;
}plug_st;

typedef struct _plug_manager_st{
	int test;
	plug_st *list;
}plug_manager_st;

struct file_operations base_fops = 
{
	read: plug_base_read,
	write: plug_base_write,
	open: plug_base_open,
	release: plug_base_release,
};

static plug_manager_st plug_manager = {'\0'};

static int __init plug_base_init(void)
{
	int ret;
	ret = register_chrdev(MAJOR_NUM, "plugbase", &base_fops);
	if(ret)
	{
		printk("regist failed.\n");	
	} else {
		printk("regist success.\n");	
	}

	return ret;
}

static void __exit plug_base_exit(void)
{
	unregister_chrdev(MAJOR_NUM, "plugbase");
}

int plug_regist(plug_st *pplug)
{
	pplug->next = plug_manager.list;	
	plug_manager.list = pplug;
	printk("regist plug success!");
	return 0;
}

static int plug_walk(void) 
{
	plug_st	*pplug = NULL;
	int a = 0, b = 2;

	printk("plug walk!\n");

	if(plug_manager.list == NULL)
	{
		printk("no plug in\n");	
	}

	pplug = plug_manager.list;
	while(pplug)
	{
		printk("in...\n");
		if(pplug->pfunc != NULL)	
			pplug->pfunc(a, b);
		pplug = pplug->next;
	}
	
	return 0;
}

static ssize_t plug_base_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
	int ret = 0;

	ret = plug_walk();

	return 0;
}

static ssize_t plug_base_write(struct file *filp, const char *buf, size_t len, loff_t * off_len)
{

	int ret = 0;

	ret = plug_walk();
	return 0;	
}

static ssize_t plug_base_open(struct inode *inode, struct file *filp)
{
	int ret = 0;

	ret = plug_walk();
	return 0;
}

static ssize_t plug_base_release(struct inode *inode, struct file *filp)
{
	return 0;
}

EXPORT_SYMBOL(plug_regist);
module_init(plug_base_init);
module_exit(plug_base_exit);
