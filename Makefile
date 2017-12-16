obj-m += killkey.o

all:
	make -C /usr/lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /usr/lib/modules/`uname -r`/build M=$(PWD) clean
