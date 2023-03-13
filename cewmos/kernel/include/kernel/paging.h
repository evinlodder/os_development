#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <initializer_list>
#include <kernel/panic.h>
#include <kernel/kmalloc.h>

namespace p_detail {
    inline bool initialized {false};
}

namespace kernel {
// note to people reading and myself: this is kinda overengineered

constexpr uint32_t PT_SIZE {1024};

constexpr bool PSE {false};

constexpr uint32_t PD_SIZE {1024};

enum class table_flags : uint8_t {
    present = 0b1,
    writable = 0b10,
    user_mode = 0b100,
    write_through = 0b1000,
    disable_cache = 0b10000,
    accessed = 0b100000,
    dirty = 0b1000000,
    global = 0b10000000,
};


enum class directory_flags : uint16_t {
    present = 0b1,
    writable = 0b10,
    user_mode = 0b100,
    write_through = 0b1000,
    disable_cache = 0b10000,
    accessed = 0b100000,
    dirty = 0b1000000,
    mb_pages = 0b1000000,
    global = 0b100000000,
};


uintptr_t get_table_virt(size_t);
void map(uintptr_t, uintptr_t, uintptr_t, uintptr_t, std::initializer_list<table_flags>, std::initializer_list<directory_flags>);

void init_paging(uintptr_t, uintptr_t, size_t);

}

#endif
