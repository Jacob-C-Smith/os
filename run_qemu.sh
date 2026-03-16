qemu-system-i386 -kernel os -s -S -d in_asm,int,guest_errors,nochain,cpu_reset -D qemu.log &
QEMU_PID=$!
x86_64-elf-gdb -ex 'set architecture i386' -ex 'target remote localhost:1234' ./os
kill $QEMU_PID
