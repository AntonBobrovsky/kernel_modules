CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
TARGET = mod_dev
TARGET2 = mod_proc

obj-m += $(TARGET).o
obj-m += $(TARGET2).o

default:
		$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
		rm -f *.o .*.cmd .*.flags *.mod.c *.order
		rm -f *.symvers
		rm -f .*.*.cmd *~ *.*~ TODO.*
		rm -fR .tmp*
		rm -rf .tmp_versions

disclean: clean
		rm *.ko
