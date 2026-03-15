#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

typedef uint64_t gdt_segdesc_t;

struct gdt_segdesc {
    uint32_t base : 32;
    uint32_t limit : 20;

    uint32_t privilege_level : 2;
    bool executable;
    bool task_seg;
    bool size_flag;
    bool granularity;
};

[[maybe_unused]]
static inline gdt_segdesc_t gdt_segdesc_init(const struct gdt_segdesc desc)
{
    return (union {
        // Broken into the fields
        struct {
            uint64_t limit15_0 : 16;
            uint64_t base23_0 : 24;

            // Access field
            uint64_t reserved0 : 1;
            uint64_t rw : 1;
            uint64_t dc : 1;
            uint64_t e : 1;
            uint64_t s : 1;
            uint64_t dpl : 2;
            uint64_t p : 1;

            uint64_t limit19_16 : 4;

            // Flags field
            uint64_t reserved1 : 2;
            uint64_t db : 1;
            uint64_t g : 1;

            uint64_t base31_24 : 8;
        } fields;

        // The raw 64bit value
        gdt_segdesc_t value;
    }) {
        .fields = {
            .limit15_0 = desc.limit,
            .base23_0 = desc.base,
            .e = desc.executable,
            .s = desc.task_seg,
            .dpl = desc.privilege_level,
            .p = true,
            .limit19_16 = desc.limit >> 16,
            .db = desc.size_flag,
            .g = desc.granularity,
            .base31_24 = desc.base >> 24,
        },
    }
        .value;
}

[[maybe_unused]]
static inline void gdt_load(const uint16_t len,
    const gdt_segdesc_t descs[static const len])
{
    static uint64_t gdtr;
    gdtr = ((uintptr_t)descs << 16) + len;
    __asm__ volatile("lgdt (%[ptr])" : : [ptr] "X"(&gdtr));
}

#endif
