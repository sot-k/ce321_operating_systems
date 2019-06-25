KARAMELLIOS SOTIRIOS 2237 skaramellios@uth.gr
CHOULIARAS ANDREAS 2143 achouliaras@uth.gr
SAMARAS VASILIOS 2144 vsamaras@uth.gr

=======================================

Copy the file patch_4 in directory /usr/src
Go to Directory /usr/src/linux-3.14.62-dev

and run the commands
	patch -p1 < ../patch_4
	sudo make
	sudo make modules_install
	sudo install 
	sudo mkinitramfs -o initrd.img-3.14.62-dev 3.14.62-dev
	sudo update_grub
reboot

the following commands mounts the virtual disk and enables the
clook module for this disk
	sudo mount /dev/sdb1 /media/test_disk
	sudo modprobe clook-iosched
	cat /sys/block/sdb/queue/scheduler
	sudo bash -c ’echo clook > /sys/block/sdb/queue/scheduler’
	cat /sys/block/sdb/queue/scheduler

move files in Experiments directory to desktop
use the commands below to test the clook scheduler
	sudo make
	sudo ./initFile
	sudo ./test1
	sudo ./test2

WARNING!
the programs must be run from Desktop while the virtual disk is mounted
