#include <types.h>
#include <arch/x86/vga.h>

#include <va.h>
#include <string.h>

void terminal_initialize(void);

void terminal_setcolor(u8 color);

void terminal_putentryat(char c, u8 color, size_t x, size_t y);

void terminal_putchar(char c);

void terminal_write(const char* data, size_t size);

void terminal_writestring(const char* data);

int terminal_printf ( const char *restrict format, ... );
