########################
# @module name: 
# @creator: 
#
# @date:
#
# first: process the else part
#	-C means goto the kernel dir , to excute the kernel makefile
#	M means go back to the current dir, then excute the part before 
#   else 
#####################

ifneq ($(KERNELRELEASE),)
	obj-m := print_plug.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -fr *.cmd *.o *.mod.c *.ko *.order *.symvers
endif
