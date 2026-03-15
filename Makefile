.PHONY: build clean image qemu kernel

kernel:
	touch os
	rm os
	nasm -felf32 src/arch/x86/boot.asm -o build/boot.o
	nasm -felf32 src/arch/x86/idt.asm -o build/idta.o
	i686-elf-gcc -g -Iinclude -c src/arch/x86/vga.c -o build/vga.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/arch/x86/idt.c -o build/idt.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/arch/x86/isr.c -o build/isr.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/os/terminal.c -o build/terminal.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/os/pack.c -o build/pack.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/stdlib/string.c -o build/string.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/stdlib/stdlib.c -o build/stdlib.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/stdlib/ctype.c -o build/ctype.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -Iinclude -c src/kernel.c -o build/kernel.o -std=c23 -ffreestanding -O0 -Wall -Wextra
	i686-elf-gcc -g -T linker.ld -o os -ffreestanding -O0 -nostdlib \
	build/boot.o \
	build/idta.o \
	build/vga.o \
	build/idt.o \
	build/isr.o \
	build/terminal.o \
	build/pack.o \
	build/string.o \
	build/stdlib.o \
	build/ctype.o \
	build/kernel.o

qemu: 
	qemu-system-i386 -kernel os -s 

clean:
	rm os build/*.o