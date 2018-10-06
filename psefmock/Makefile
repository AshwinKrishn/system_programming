obj-m += pscode.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm *.ko *.o *.symvers *.order *.mod*
