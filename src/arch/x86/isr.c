/** !
 * interrupt service routine implementation
 * 
 * @file src/arch/x86/isr.c
 * 
 * @author Jacob Smith
 */

// header file
#include <arch/x86/isr.h>

// data
fn_isr *_isr_handlers[256] = 
{
    [ISR_DIVIDE_ERROR] = isr_divide_error, 
    
};

fn_isr *_isr_wrappers[256] = 
{
    [ISR_DIVIDE_ERROR] = isr_fault_divide_by_zero, 
};

int isr_initialize ( void ) 
{

    // initialized data
    idt_descriptor _idt_descriptors[256] = { 0 };

    // construct idt descriptors
    for (size_t i = 0; i < 256; i++)
        idt_descriptor_construct(
            &_idt_descriptors[i],
            _isr_wrappers[i] ? _isr_wrappers[i] : isr_default, 
            1<<3,
            IDT_GATE_INTERRUPT | IDT_PRIVILEGE0 | IDT_PRESENT
        );

    // set the idt
    idt_set(_idt_descriptors, 256);

    // success
    return 1;
}

void isr_default ( void ) { terminal_writestring("default ISR\n"); }
void isr_divide_error ( void ) { terminal_writestring("divide by zero ISR\n"); }
void isr_80h ( void ) { terminal_writestring("INT 0x80\n"); }
