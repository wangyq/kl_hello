
TARGET=proc_hello
KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
obj-m += $(TARGET).o

all:
	make -C $(KDIR) M=$(PWD) modules

.PHONY:install
install:
	insmod $(TARGET).ko

.PHONY:uninstall
uninstall:
	rmmod $(TARGET)

.PHONY:clean
clean:
	make -C $(KDIR) M=$(PWD) clean
#	-rm *.ko
#	-rm *.o
#	-rm -f Mo.*
#	-rm *.mod.*
#	-rm *.order
#	-rm *.symvers
##	make -C $(KDIR) M=$(PWD) clean

