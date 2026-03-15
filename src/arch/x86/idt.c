/** !
 * interrupt descriptor table implementation
 * 
 * @file src/arch/x86/idt.c
 * 
 * @author Jacob Smith
 */

// header file
#include <arch/x86/idt.h>

// function declarations
int idt_descriptor_construct 
(
    idt_descriptor *p_idt_descriptor,
    void           *p_offset,
    u16             selector,
    u8              type
)
{

    // populate fields
    *p_idt_descriptor = (idt_descriptor)
    {
        .p_offset = p_offset,
        .selector = selector,
        .type = type
    };

    // success
    return 1;
}

int idt_descriptor_pack ( void *p_buffer, const void *p_value )
{

    // initialized data
    idt_descriptor *p_idt_descriptor = (idt_descriptor *) p_value;
    char *p = p_buffer;
    size_t offset = (size_t) p_idt_descriptor->p_offset;

    // pack the idt entry
    p += pack_pack(p, "%i16%i16%i8%i8%i16",
        offset & 0xffff,
        p_idt_descriptor->selector,
        0,
        p_idt_descriptor->type,
        (offset >> 16) & 0xffff
    );

    // done
    return 8;
}

int idt_set ( idt_descriptor *p_descriptors, int quantity )
{   

    // external declarations
    extern void idt_load(void *);

    // initialized data
    char *p = alloc(sizeof(idt_descriptor) * quantity);
    char *q = p;
    char *r = alloc(sizeof(u16) + sizeof(void *));

    // pack each IDT entry
    for (int i = 0; i < quantity; i++)
        p += idt_descriptor_pack(p, &p_descriptors[i]);

    // pack the IDTR
    pack_pack(r, "%i16%i32", quantity*8-1, (u32) q);

    // load the IDT
    idt_load(r);

    // success
    return 1;
}