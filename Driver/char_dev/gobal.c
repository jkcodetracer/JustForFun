/*
 * @FileName: gobal.c
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
 * @Date: 2012年07月26日星期四22:36:08
 * 
 */ 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM	(240)	//major dev id

static int global_var = 123;

static ssize_t globalvar_read(struct file*, char*, size_t, loff_t*);
static ssize_t globalvar_write(struct file*, const char*,size_t, loff_t*);

//init fileoperation
struct file_operations global_fops = {
	read: globalvar_read,
	write: globalvar_write,
};

static ssize_t
globalvar_read(struct file* filp, char *buf, size_t len, loff_t *off)
{
	int ret = 0;	

	ret = copy_to_user(buf, &global_var, sizeof(global_var));
	if(ret)
	{
		return -EFAULT;
	}

	return sizeof(global_var);
}

static ssize_t
globalvar_write(struct file *filp, const char *buf, size_t len , loff_t *off)
{
	int ret = 0;

	ret = copy_from_user(&global_var, buf, sizeof(global_var));
	if(ret)
	{
		return -EFAULT;
	}

	return sizeof(global_var);
}

//init char dev
static int
__init globalvar_init(void)
{
	int ret;
	
	ret = register_chrdev(MAJOR_NUM, "globalvar", &global_fops);
	if(ret)
	{
		printk("globalvar register_chrdev  failed.");
	} else {
		printk("glovalvar register_chrdev success.");	
	}

	return ret;
}

static void
__exit globalvar_exit(void)
{
	int ret;

	unregister_chrdev(MAJOR_NUM, "globalvar");
	if(ret)
	{
		printk("globalvar unregister failed");
	} else {
		printk("globalvar unregister success.");
	}
}


module_init(globalvar_init);
module_exit(globalvar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("code_tracer");

