.PHONY: build clean image qemu bootloader

bootloader:
	nasm -f bin boot.asm -o boot.bin
	nasm -f bin stage2.asm -o stage2.bin

image: bootloader
	dd if=/dev/zero of=os.img bs=512 count=2048
	dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc
	dd if=stage2.bin of=os.img bs=512 seek=1 count=16 conv=notrunc

qemu: image
	qemu-system-i386 -hda os.img

clean: