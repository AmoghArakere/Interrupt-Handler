gedit p2.c
gedit divzero.c
gedit Makefile
make
gcc -o p2 p2.c
sudo insmod divzero.ko
sudo mknod /dev/divzero c 240 0
sudo chmod 666 /dev/divzero
./p2
./divzero
sudo dmesg | tail
sudo rmmod divzero
sudo dmesg | tail
