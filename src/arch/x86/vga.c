#include <arch/x86/vga.h>

u8 vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

u16 vga_entry(u8 uc, u8 color) 
{
	return (u16) uc | (u16) color << 8;
}
