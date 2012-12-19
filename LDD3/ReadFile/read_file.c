/*
 * @FileName: read_file.c
 * @Author: wzj
 * @Brief: 
 * 		1.在驱动里面写文件.... 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月04日星期一22:57:13
 * 
 */ 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static char buf[] = "你好\n";
static char buf1[10];

int __init
hello_init(void)
{
	struct file *fp;
	mm_segment_t fs;
	loff_t pos;

	printk("hello enter\n");
	//打开一个文件
	fp = filp_open("/tmp/test", O_RDWR | O_CREAT, 0644);

	if(IS_ERR(fp))
	{
		printk("create file error\n");
		return -1;
	}
	//保存当前进程虚拟地址上限
	fs = get_fs();
	//设置当前进程虚拟地址上限为4G
	set_fs(KERNEL_DS);
	pos = 0;
	//写文件
	vfs_write(fp, buf, sizeof(buf), &pos);
	pos = 0;
	//读文件
	vfs_read(fp, buf1, sizeof(buf), &pos);
	//这是另一种写法
	fp->f_pos = sizeof(buf);
	fp->f_op->write(fp, buf, sizeof(buf), &fp->f_pos);

	printk("read: %s\n" , buf1);
	//关闭文件	
	filp_close(fp, NULL);
	//还原地址空间上限
	set_fs(fs);
	return 0;
}

void __exit
hello_exit(void)
{
	printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
