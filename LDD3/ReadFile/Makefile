########################
# @module name: 
# @creator: 
#
# @date:
#
#####################

ifneq ($(KERNELRELEASE),)
	obj-m := read_file.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
