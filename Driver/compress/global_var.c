/**
 * @file  global_var.c
 * @author  wzj
 * @brief  competation
 * @version 1.1
 * @note  
 * @date: 2012年08月02日星期四23:39:28
 * 
 */ 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>


MODULE_LICENSE("GPL");

#define MAJOR_NUM	(239)

static ssize_t global_var_read(struct file*, char*, size_t, loff_t *);
static ssize_t global_var_write(struct file*, const char*, size_t, loff_t *);
static int global_var_open(struct inode *inode, struct file *filp);
static int global_var_release(struct inode *inode, struct file *filp);

struct file_operations globalvar_fops =
{
	read:global_var_read,
	write:global_var_write,
	open:global_var_open,		
	release:global_var_release,
};

static int global_var = 0;
static struct semaphore sem;
static int globalvar_count = 0;
static spinlock_t spin = SPIN_LOCK_UNLOCKED;

static int __init globalvar_init(void)
{
	int ret;
	ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops);
	if(ret)
	{
		printk("register failed.");
	} else {
		printk("register success");
		init_MUTEX(&sem);
	}
	return ret;	
}

static void __exit globalvar_exit(void)
{
	int ret;
	unregister_chrdev(MAJOR_NUM, "globalvar");
	if(ret)
	{
		printk("globalvar unregister failed");
	} else {
		printk("globalvar unregister_chrdev oK");
	}
}

static ssize_t global_var_read(struct file *filp, char *buf, size_t len,loff_t *off)
{
	/* get semaphore */
	if(down_interruptible(&sem))
	{
		return -ERESTARTSYS;
	}

	if(copy_to_user(buf, &global_var, sizeof(int)))
	{
		up(&sem);
		return -EFAULT;
	}

	up(&sem);

	return sizeof(int);
}

static ssize_t global_var_write(struct file *filp, const char *buf, size_t len, loff_t *off)
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
	return sizeof(int);
}

static int global_var_open(struct inode *inode, struct file *filp)
{
	spin_lock(&spin);	

	if(globalvar_count)
	{
		spin_unlock(&spin);
		return -EBUSY;
	}

	globalvar_count++;
	spin_unlock(&spin);

	return 0;
}

static int global_var_release(struct inode *inode, struct file *filp) 
{
	spin_lock(&spin);
	globalvar_count--;
	spin_unlock(&spin);

	return 0;
}

module_init(globalvar_init);
module_exit(globalvar_exit);
