#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

typedef uint64_t gdt_segdesc_t;

struct gdt_segdesc {
    uint32_t base : 32;
    uint32_t limit : 20;

    uint32_t privilege_level : 2;
    bool read_write;
    bool executable;
    bool not_task_seg;
    bool present;
    bool size_flag;
    bool granularity;
};

#define _gdt_segdesc_f(desc, field) ((uint64_t)(desc).field)
#define gdt_segdesc_init(d)                                                                                                                                                                                           \
    (gdt_segdesc_t)(                                                                                                                                                                                                  \
        ((_gdt_segdesc_f(d, limit) & 0xffff) | (_gdt_segdesc_f(d, limit) >> 16 << 48))                                                                                                                                \
        | (((_gdt_segdesc_f(d, base) & 0xffffff) << 16) | ((_gdt_segdesc_f(d, base) & 0xff000000) << 32))                                                                                                             \
        | ((_gdt_segdesc_f(d, read_write) << 41) | (_gdt_segdesc_f(d, executable) << 43) | (_gdt_segdesc_f(d, not_task_seg) << 44) | (_gdt_segdesc_f(d, privilege_level) << 45) | (_gdt_segdesc_f(d, present) << 47)) \
        | ((_gdt_segdesc_f(d, size_flag) << 54) | (_gdt_segdesc_f(d, granularity) << 55)))

[[maybe_unused]]
static inline void gdt_load(const uint16_t len,
    const gdt_segdesc_t descs[static const len])
{
    static uint64_t gdtr;
    gdtr = ((uint64_t)(uintptr_t)descs << 16) + (len * sizeof(gdt_segdesc_t));
    __asm__ volatile("lgdt (%[ptr])" : : [ptr] "m"(gdtr));
}

#endif
