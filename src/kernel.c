#include <types.h>
#include <arch/x86/vga.h>
#include <os/terminal.h>
#include <os/pack.h>
#include <string.h>
#include <stdlib.h>

void kernel_early ( void )
{
	terminal_initialize();
}

void kernel_main ( void ) 
{
	kernel_early();
	terminal_writestring("Hello, kernel World!\n");
	void *p = alloc(100);
	pack_pack(p, "%4i8",'a','b','c',0);
	terminal_writestring(p);
}