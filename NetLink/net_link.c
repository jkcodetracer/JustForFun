/*
 * @FileName: net_link.c
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
 * @Date: 2012年02月10日星期五23:19:00
 * 
 */ 
#include<linux/string.h>
#include<linux/stat.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/socket.h>
#include<linux/types.h>
#include<linux/capability.h>
#include<linux/errno.h>
#include<linux/stat.h>
#include<linux/skbuff.h>
#include<linux/netlink.h>
#include<net/sock.h>

struct sock *nl_sk = NULL;
static void nl_data_ready(struct sock *sk, int len) 
{
	wake_up_interruptible(sk->sk_sleep);
}

int netlink_test()
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh = NULL;
	int err;
	u32 pid;
	
	nl_sk = netlink_kernel_create(&init_net, 28, 0, nl_data_ready, NULL, THIS_MODULE);
	//nl_sk = netlink_kernel_create(28,  nl_data_ready);
	if (!nl_sk)
	{
		printk("Fail to create 1c user event netlink socket.\n");
		return 0;
	}

	skb = skb_recv_datagram(nl_sk, 0, 0, &err);
	nlh = (struct nlmsghdr *) skb->data;
	printk("%s: received netlink message payload: %s", __FUNCTION__, NLMSG_DATA(nlh));
	pid = nlh->nlmsg_pid;

	nlh->nlmsg_len = skb->len;
	NETLINK_CB(skb).pid = 0;
	//NETLINK_CB(skb).dst_pid = pid;
	NETLINK_CB(skb).dst_group = 1;
	netlink_broadcast(nl_sk, skb, 0, 1, GFP_KERNEL);

	return 1;
}

static int __init my_module_init(void)
{
	printk("Initializing Netlink Socket\n");
	if (netlink_test())
	{
		printk("Message has send\n");
	}
	else
	{
		printk("send error\n");
	}
	return 0;
}

static void __exit my_module_exit(void)
{
	if (nl_sk)
	{
		sock_release(nl_sk->sk_socket);
		printk("Goodbye\n");
	}
	else
	{
		printk("no sock, release error\n");
	}
}

module_init(my_module_init);
module_exit(my_module_exit);

