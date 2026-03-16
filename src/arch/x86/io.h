/** !
 * I/O interface
 * 
 * @file src/arch/x86/io.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <types.h>
#include <stdlib.h>

// os
#include <os/interfaces.h>
#include <os/terminal.h>

// arch
#include <arch/x86/idt.h>

// enumeration definitions
//

// forward declarations
void out_byte  ( u16 port, u8  value );
void out_word  ( u16 port, u16 value );
void out_dword ( u16 port, u32 value );

u8  in_byte  ( u16 port );
u16 in_word  ( u16 port );
u32 in_dword ( u16 port );

