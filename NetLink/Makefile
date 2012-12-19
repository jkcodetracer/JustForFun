MODULE_NAME := net_link
obj-m+=$(MODULE_NAME).o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
	gcc -g -o sender sender.c

clean:
	rm -f *.ko *.o *.cmd sender $(MODULE_NAME).mod.c Module.symvers
in:
	insmod net_link.ko
rm:
	rmmod net_link
sp:
	cat /proc/net/netlink
ru:
	./sender
sm:
	dmesg -c

