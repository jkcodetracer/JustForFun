/**
 * \file async_io_driver.c
 * \author  wzj
 * \brief 支持异步I/O 的驱动
 * \version 
 * \note  
 * \date: 2012年10月01日星期一23:33:28
 */ 

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/fcntl.h>
#include <linux/poll.h>

MODULE_LICENSE("GPL");

#define LEN 30
#define init_MUTEX(LOCKNAME) sema_init(LOCKNAME, 1)
#define DEVICE_NAME "CDEV_AIO"

static struct class *cdev_class;

struct ct_aio{
	struct cdev dev_c;
	dev_t dev;
	char mem[LEN];
	int flag;
	struct semaphore sem;	/* 并发控制用的信号量 */
	wait_queue_head_t r_wait;	/* 阻塞读用的等待队列头 */	
	struct fasync_struct *async_queue;	/* 异步结构题指针，用于读 */
};

struct ct_aio asyc_dev;

static int asyc_io_fasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd, filp, mode, &asyc_dev.async_queue);
}
/* 释放文件 */
int asyc_io_release(struct inode *inode, struct file *filp)
{
	/* 将文件从异步列表中删除 */
	asyc_io_fasync(-1, filp, 0);
}

/* 写文件 */
static ssize_t asyc_write(struct file *filp, 
						  const char __user *buf, 
						  size_t count, 
						  loff_t *ppos)
{
	int ret = count;
	printk("In asyc_write!\n");
	down(&asyc_dev.sem);
	memset(asyc_dev.mem, 0, LEN);
	if(copy_from_user(asyc_dev.mem, buf, count))
	{
		up(&asyc_dev.sem);
		return -EFAULT;
	}

	printk("kernel device: %s  and the length is %d\n",
			asyc_dev.mem, count);
	up(&asyc_dev.sem);
	asyc_dev.flag = 1;
	
	if(asyc_dev.async_queue)
		kill_fasync(&asyc_dev.async_queue, SIGIO, POLL_IN);
	
	wake_up_interruptible(&asyc_dev);

	return ret;
}

static ssize_t asyc_read(struct file *filp, 
						 char *buf, 
						 size_t len,
						 loff_t *off)
{
	int ret = len;
	
	printk("In asyc_read\n");
	if(wait_event_interruptible(asy_dev.r_wait, sayc_device.flag != 0))
	{
		return -ERESTARTSYS;
	}

	if(down_interruptible(&asyc_dev.sem))
	{
		return -ERESTARTSYS;
	}

	asyc_device.flag = 0;

	if(copy_to_user(buf, asyc_dev.mem, len))
	{
		up(&async_dev.sem);
		return -EFAULT;
	}

	up(&asyc_dev.sem);

	return ret;
}

struct file_operation asyc_fops = {
	read: asyc_read,
	write: asyc_write,	
	fasync: asyc_io_fasync,
	release: asyc_io_release,
};

static int __init asyc_init(void)
{
	int ret, err;

	ret = alloc_chrdev_region(&(asyc_devic.dev), 0, 1, DEVICE_NAME);
}
