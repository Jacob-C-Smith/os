#include "arch/x86/gdt.h"
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
	gdt_load(3, (const gdt_segdesc_t []){
	         	gdt_segdesc_init((struct gdt_segdesc){}),
	         	gdt_segdesc_init(((struct gdt_segdesc){
	         	                 	.base = 0x0040'0000,
	         	                 	.limit = 0x3ff,

								    .privilege_level = 0,
								    .executable = true,
								    .read_write = true,
								    .present = true,
								    .not_task_seg = true,
								    .size_flag = true,
								    .granularity = true,
	         	                 })),
	         	gdt_segdesc_init(((struct gdt_segdesc){
	         	                 	.base = 0x0080'0000,
	         	                 	.limit = 0x3ff,

								    .privilege_level = 0,
								    .executable = false,
								    .read_write = true,
								    .present = true,
								    .not_task_seg = true,
								    .size_flag = true,
								    .granularity = true,
	         	                 	})),
	         });
	
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
