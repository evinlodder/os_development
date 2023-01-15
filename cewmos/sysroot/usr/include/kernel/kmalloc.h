#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>

namespace kmalloc {
    extern bool enabled;
}

namespace kernel {
    uint32_t kmalloc_aligned(uint32_t size);
    uint32_t kmalloc_phys(uint32_t size, uint32_t* phys);
    uint32_t kmalloc_ap(uint32_t size, uint32_t* phys);
    uint32_t kmalloc(uint32_t size);

    void disable_kmalloc();
}


#endif
