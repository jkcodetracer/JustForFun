/**
 * \file intr.c
 * \author  wzj
 * \brief 
 	simple intr program
 * \version 
 * \note  
 * \date: 2012年10月30日星期二23:53:53
 * 
 * discript your detail info.
 */ 
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

static int irq;
static char *interface;

module_param(interface, charp, 0644);
module_param(irq, int, 0644);

static irqreturn_t myinterrupt(int irq, void *dev_id)
{
	static int mycount = 0;
		
	if(mycount < 10)
	{
		printk("Interrupts\n");
		mycount++;
	}

	return IRQ_NONE;
}

static int __init myirqtest_init(void)
{
	printk("My module worked !\n");
	if(request_irq(irq, &myinterrupt, IRQF_SHARED, interface, &irq))
	{
		printk("myirqtest: cannot register IRQ %d\n", irq);
		return -EIO;
	}

	printk("%s Request on IRQ %d succeeded\n", interface, irq);
	return 0;
}

static void __exit myirqtest_exit(void)
{
	printk("Unload my module.\n");
	free_irq(irq, &irq);
	printk("Freeing IRQ %d\n", irq);

	return ;
}

module_init(myirqtest_init);
module_exit(myirqtest_exit);
MODULE_LICENSE("GPL");
