/** !
 * interrupt descriptor table interface
 * 
 * @file src/arch/x86/idt.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <types.h>

// os
#include <os/interfaces.h>

// enumeration definitions
enum idt_gate_type_e
{
    IDT_GATE_TASK = 0b0101,
    IDT_GATE_INTERRUPT = 0b1110,
    IDT_GATE_TRAP = 0b1111
};

enum idt_privilege_level_e
{
    IDT_PRIVILEGE0 = 0,
    IDT_PRIVILEGE1 = 1<<0,
    IDT_PRIVILEGE2 = 1<<1,
    IDT_PRIVILEGE3 = (1<<0) | (1<<1),
};

// structure definitions
struct idt_descriptor_s;
struct idt_s;

// type definitions
typedef struct idt_descriptor_s idt_descriptor;
typedef struct idt_s idt;

// function definitions
/// constructors
/** !
 * Construct a interrupt descriptor table entry
 * 
 * @param p_idt_descriptor result
 * @param p_offset         the address of the interrupt service routine
 * 
 * @return 1 on success, 0 on error
 */
int idt_descriptor_construct 
(
    idt_descriptor *p_idt_descriptor,
    void           *p_offset,
    u16             selector,
    u8              type
);

/// pack
fn_pack idt_descriptor_pack;

/// set
/** !
 * update the interrupt descriptor table register
 * 
 * @param _p_descriptors an array of interrupt descriptor table pointers
 * @param quantity       the quantity of interrupt descriptor table entries
 * 
 * @return 1 on success, 0 on error
 */
int idt_set ( idt_descriptor *_p_descriptors[], int quantity );
