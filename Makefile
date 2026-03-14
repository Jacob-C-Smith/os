.PHONY: build clean image qemu kernel

kernel:
	rm os
	nasm -felf32 src/arch/x86/boot.asm -o build/boot.o
	i686-elf-gcc -Iinclude -c src/arch/x86/vga.c -o build/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -Iinclude -c src/os/terminal.c -o build/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -Iinclude -c src/stdlib/string.c -o build/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -Iinclude -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o os -ffreestanding -O2 -nostdlib \
	build/boot.o \
	build/vga.o \
	build/terminal.o \
	build/string.o \
	build/kernel.o

qemu: 
	qemu-system-i386 -kernel os -s 

clean: