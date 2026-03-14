#include <types.h>
#include <arch/x86/vga.h>
#include <os/terminal.h>
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
	char *a = strdup("ABC", 4);

	terminal_writestring(a);
}