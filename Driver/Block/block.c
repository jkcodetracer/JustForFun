/**
 * \file block.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月07日星期二00:07:06
 * 
 */ 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>		/*file_operations */
#include <asm/uaccess.h>	
#include <linux/wait.h>		/*wait_queue_head_t*/
#include <linux/semaphore.h>	/*semaphore*/
#include <linux/sched.h>	/* for TASK_INTERRUPTIBLE */

MODULE_LICENSE("GPL");

#define MAJOR_NUM	(239)

static ssize_t globalvar_read(struct file *, char*,size_t, loff_t*);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);

struct file_operations globalvar_fops =
{
	read: globalvar_read,
	write: globalvar_write,
};

static int global_var = 0;
static struct semaphore sem;
static wait_queue_head_t outq;
static int flag = 0;

static int __init globalvar_init(void)
{
	int ret;

	ret = register_chrdev(MAJOR_NUM, "glovalvar", &globalvar_fops);
	if(ret)
	{
		printk("globalvar register failure.");
	} else {
		printk("globalvar register success.");
		init_MUTEX(&sem);
		init_waitqueue_head(&outq);
	}

	return ret;
}

static void __exit globalvar_exit(void)
{
	 unregister_chrdev(MAJOR_NUM, "globalvar");
}

static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
	/* 让进程排队 */	
	if(wait_event_interruptible(outq, flag!= 0))
	{
		return -ERESTARTSYS;
	}

	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}

	flag = 0;
	if(copy_to_user(buf, &global_var, sizeof(int)))
	{
		up(&sem);
		return -EFAULT;
	}

	up(&sem);

	return sizeof(global_var);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len , loff_t *off)
{
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}
	if(copy_from_user(&global_var, buf, sizeof(int)))
	{
		up(&sem);
		return -EFAULT;
	}

	up(&sem);
	flag = 1;

	wake_up_interruptible(&outq);

	return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit);
