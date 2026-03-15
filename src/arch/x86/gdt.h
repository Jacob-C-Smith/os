/** !
 * global descriptor table interface
 * 
 * @file src/arch/x86/gdt.h
 */

// header guard
#pragma once

// standard library
#include <types.h>

// os
#include <os/interfaces.h>

// enumeration definitions
enum gdt_access_e
{
    GDT_ACCESS_ACCESSED   = 1<<0,
    GDT_ACCESS_READWRITE  = 1<<1,
    GDT_ACCESS_GROWDOWN   = 1<<2,
    GDT_ACCESS_CONFORMING = 1<<2,
    GDT_ACCESS_EXECUTABLE = 1<<3,
    GDT_ACCESS_CODEDATA   = 1<<4,
    GDT_ACCESS_PRIVILEGE0 = 0,
    GDT_ACCESS_PRIVILEGE1 = 1<<5,
    GDT_ACCESS_PRIVILEGE2 = 1<<6,
    GDT_ACCESS_PRIVILEGE3 = (1<<5) | (1<<6),
    GDT_ACCESS_PRESENT    = 1<<7,
};

enum gdt_flags_e
{
    GDT_FLAGS_BYTE_GRANULARITY = 0,
    GDT_FLAGS_PAGE_GRANULARITY = 1<<3,
};

// structure definitions
struct gdt_descriptor_s;
struct gdt_s;

// type definitions
typedef struct gdt_descriptor_s gdt_descriptor;
typedef struct gdt_s gdt;

// function definitions
/// constructors
/** !
 * Construct a global descriptor table entry
 * 
 * @param p_gdt_descriptor result
 * @param p_base           the base address of the entry
 * @param p_limit          the upper limit of the entry
 * @param access           the access byte
 * @param flags            the flags 
 * 
 * @return 1 on success, 0 on error
 */
int gdt_descriptor_construct 
(
    gdt_descriptor *p_gdt_descriptor,
    void           *p_base,
    void           *p_limit, 
    u8             access,
    u8             flags
);

/// pack
fn_pack gdt_descriptor_pack;

/// set
/** !
 * update the global descriptor table register
 * 
 * @param _p_descriptors an array of global descriptor table pointers
 * @param quantity       the quantity of global descriptor table entries
 * 
 * @return 1 on success, 0 on error
 */
int gdt_set ( gdt_descriptor *_p_descriptors[], int quantity );
