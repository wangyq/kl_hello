TARGET=hello
KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
obj-m +=$(TARGET).o

default:
	make -C $(KDIR) M=$(PWD) modules

.PHONY:install
install:
	insmod $(TARGET).ko

.PHONY:uninstall
uninstall:
	rmmod $(TARGET).ko

.PHONY:clean
clean:
	-rm *.ko
	-rm *.o
	-rm -f Mo.*
	-rm *.mod.*

##	make -C $(KDIR) M=$(PWD) clean

