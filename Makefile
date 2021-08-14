KVER=$(shell readlink /usr/src/linux | cut -f2- -d-)
obj-m+=hid-advantage2.o

all: probe

probe: install
	modprobe -r hid-advantage2 || true
	modprobe hid-advantage2

modules:
	make -C /lib/modules/$(KVER)/build/ M=$(PWD) modules
install: modules
	make -C /lib/modules/$(KVER)/build/ M=$(PWD) modules_install
clean:
	make -C /lib/modules/$(KVER)/build/ M=$(PWD) clean
