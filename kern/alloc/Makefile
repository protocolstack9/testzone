DRIVER_OBJS = alloc_work.o

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /home/freestyle/2kitkat-mr1/kernel/
PWD := $(shell pwd)

obj-m := alloc_works.o
alloc_works-objs := $(DRIVER_OBJS)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
#all:
#	make -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=<...> modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
