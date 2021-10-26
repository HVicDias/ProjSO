test:
	nasm -felf32 config.s -o config.o
	i686-linux-gnu-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	i686-linux-gnu-g++ -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o config.o -lgcc
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
	qemu-system-x86_64 -boot d -cdrom myos.iso -m 32

qemu:
	qemu-system-x86_64 -boot d -cdrom myos.iso -m 32