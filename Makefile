obj-m += main.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod main.ko
	sudo rmmod main.ko
	sudo dmesg

load:
	sudo insmod main.ko

unload:
	sudo rmmod main

repare:
	sudo apt install --reinstall linux-headers-$(shell uname -r)
