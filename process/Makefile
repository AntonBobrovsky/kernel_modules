obj-m += mod_process.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
		rm -f *.o .*.cmd .*.flags *.mod.c *.order
		rm -f *.symvers
		rm -f .*.*.cmd *~ *.*~ TODO.*
		rm -fR .tmp*
		rm -rf .tmp_versions
		rm -f *.h.gch 

disclean: clean
		rm *.ko
