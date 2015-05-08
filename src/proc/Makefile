
TARGET=proc_hello
KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)

SRC_FILE_TYPE := c
SRC_DIR = $(PWD) 

VPATH := $(SRC_DIR)

FIND_SRC_FILES = $(foreach dir, $(VPATH), $(wildcard $(dir)/*.$(SRC_FILE_TYPE)))
SRC_FILES = $(notdir $(FIND_SRC_FILES))

OBJ_FILES = $(SRC_FILES:.$(SRC_FILE_TYPE)=.o)

module-objs := ${OBJ_FILES}
obj-m := $(TARGET).o

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

