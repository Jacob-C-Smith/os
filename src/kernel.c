#include <types.h>
#include <arch/x86/vga.h>
#include <arch/x86/idt.h>
#include <arch/x86/isr.h>
#include <os/terminal.h>
#include <os/pack.h>
#include <string.h>
#include <stdlib.h>

void kernel_early ( void )
{

	// initialize the terminal
	terminal_initialize();

	// TODO: set up the GDT
	
	// set up ISR's
	isr_initialize();
    terminal_writestring("Initialized IDT\n");

	// - set up PCI
	// - set up PIC
	// - set up PIT
	// - set up keyboard
	// - set up mouse
	// - set up IDE

}

void kernel_main ( void ) 
{

	// early
	kernel_early();

	// hello
    terminal_writestring("Kernel\n");

}