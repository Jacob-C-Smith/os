.PHONY: build clean image qemu kernel

kernel:
	nasm -felf32 boot.asm -o build/boot.o
	i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o os -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc

qemu: 
	qemu-system-i386 -kernel os -s 

clean: