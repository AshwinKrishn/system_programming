obj-m += kthreadwork.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	rm *.ko *.mod.* *.order *.sym* *.o 
