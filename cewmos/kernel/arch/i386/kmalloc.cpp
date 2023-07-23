#include <kernel/kmalloc.h>
#include <kernel/panic.h>
#include <stdio.h>
extern "C" uint32_t _kernel_end;
uint32_t placement_address {(uint32_t)&_kernel_end};
uint32_t mem_beginning {(uint32_t)&_kernel_end};

bool kmalloc::enabled = true;

struct kmalloc_meta {
    uint32_t size;
    kmalloc_meta* next;
    kmalloc_meta* last;
} __attribute__((packed));

static constexpr uint32_t free_list_size {15};

kmalloc_meta* free_list[free_list_size] {}; // head will always be the lowest memory chunk available in memory

kmalloc_meta* last_header_location = (kmalloc_meta*)mem_beginning;

// FUNCTIONS RELATED TO FREEING

static void insert_header(kmalloc_meta* header) {
    if(!free_list[0]) {
        free_list[0] = header;
        return;
    }

    size_t i{};
    for(; (uint32_t)free_list[i] < (uint32_t)header && i < free_list_size && free_list[i]; ++i); //find index to put header in

    if(free_list[i]) {
        for(size_t p{i}; p < free_list_size - 1; ++p) {
            free_list[p + 1] = free_list[p]; //shift the rest of the list over (since it isn't empty (we checked earlier))
        }
    }

    free_list[i] = header; //then place the value in
}

static void remove_header(kmalloc_meta* header) {
    for(size_t i{}; i < free_list_size; ++i) { //loop through list to find index of header
        if(free_list[i] == header) { //found, now shift the rest of them over
            free_list[free_list_size - 1] = nullptr;
            for(size_t p{free_list_size - 1}; p > i; --p) {
                free_list[p - 1] = free_list[p];
            }
            return;
        }
    }
    kernel::panic::panic("HEADER NOT IN FREE LIST", "", true);
}

static uint32_t free_count {0};

static bool fl_contains(kmalloc_meta* header) {
    for(size_t i{}; i < free_list_size; ++i) {
        if(free_list[i] == nullptr) {
            break;
        }

        if(free_list[i] == header) {
            return true;
        }
    }
    return false;
}

#include <string.h>
static void compress_memory() {
    kmalloc_meta* iter = (kmalloc_meta*) mem_beginning;

    while(iter->next) {
        kmalloc_meta* most_compressed_next = (kmalloc_meta*)((uint32_t)iter + sizeof(kmalloc_meta) + iter->size);

        while(fl_contains(iter->next)) { //while next header is free, get rid of it
            iter->next = iter->next->next;
        }

        if(!iter->next)
            break;

        if(iter->next != most_compressed_next && (((uint32_t)iter->next + sizeof(kmalloc_meta)) & 0xFFF)) { //if (actual next != most compressed next)
            memmove(most_compressed_next, iter->next, iter->next->size + sizeof(kmalloc_meta)); //using memmove instead of memcpy because pointers are almost guranteed to overlap
                                                                                         iter->next = most_compressed_next;
        }

        iter = iter->next;
    }

    //reset locations
    last_header_location = iter;
    placement_address = (uint32_t)iter + sizeof(kmalloc_meta) + iter->size;

    for(size_t i{}; i < free_list_size; ++i) {
        free_list[i] = nullptr;
    }
}

static uint32_t allocated_blocks{0};

void kernel::kfree(void* ptr) {
    kmalloc_meta* header = (kmalloc_meta*) ((uint32_t)ptr - sizeof(kmalloc_meta));
    ++free_count;
    --allocated_blocks;
    if(free_count >= free_list_size) {
        compress_memory();
        free_count = 0;
    }

    insert_header(header);
}


static uint32_t find_header_alloc_spot(size_t size, bool aligned) {
    size_t i{};

    kmalloc_meta* iter = free_list[i];
    if(!iter) {
        return placement_address;
    }

    auto is_aligned = [&](uint32_t addr) { return aligned ? (addr & 0xFFF) == 0 : true; };
    if(allocated_blocks == 0) //if there are no allocated blocks return beginning of memory
        return mem_beginning;
    while(iter->size < size || !is_aligned((uint32_t)(iter) + sizeof(kmalloc_meta))) {
        iter = free_list[++i];
        if(!iter) {
            return placement_address;
        }
    }
    //if we've found a suitable spot, remove freed header from list and return its location
    remove_header(iter);
    return (uint32_t)iter;
}

//

static uint32_t end_of_kernel_mem = 0xC03FDFFF; // this is the end of the kernel's mapped memory

static uint32_t kmalloc_impl(uint32_t size, bool aligned, uint32_t* phys) {
    if(!kmalloc::enabled) {
        kernel::panic::panic("kmalloc is disabled", "", true);
    }

    if(aligned) {
        if((placement_address & 0xfffff000) + 0x1000 > end_of_kernel_mem) {
            kernel::panic::panic("ALLOCATING ALIGNED MEMORY WOULD OVERRIDE MBINFO", "", true);
        }

        uint32_t next_page = (placement_address & 0xfffff000) + 0x1000;
        if(placement_address > next_page - sizeof(kmalloc_meta)) {
            next_page += 0x1000;
            if(next_page > end_of_kernel_mem) {
                kernel::panic::panic("COULDN'T FIND ALIGNED SPOT FOR DATA", "", true);
            }
        }

        placement_address = next_page - sizeof(kmalloc_meta); //advance to next page

        //NOTE: I HAVEN'T PROPERLY IMPLEMENTED BEHAVIOR IF ALIGNED. I WILL GET TO THAT IF I NEED TO.
    }

    size_t alloc_spot = find_header_alloc_spot(size, aligned);
    if(alloc_spot == placement_address) {
        //check if we can fit memory
        if((alloc_spot + sizeof(kmalloc_meta) + size) > end_of_kernel_mem) {
            kernel::panic::panic("ALLOCATING MEMORY WOULD OVVERIDE MBINFO", "", true);
        }
    }
    kmalloc_meta* header = (kmalloc_meta*) alloc_spot;
    header->size = size;
    header->next = nullptr;

    ++allocated_blocks;

    if(alloc_spot == placement_address) { //if there were no suitable free spots
        if(allocated_blocks == 1) {
            header->last = nullptr;
        }
        else {
            header->last = last_header_location;
            last_header_location->next = header;
        }

        last_header_location = header;

        placement_address += sizeof(kmalloc_meta);

        if(phys) {
            *phys = placement_address;
        }

        uint32_t tmp = placement_address;
        placement_address += size;
        return tmp;
    } else {
        if(phys) {
            *phys = alloc_spot + sizeof(kmalloc_meta);
        }
        return alloc_spot + sizeof(kmalloc_meta);
    }
}

uint32_t kernel::kmalloc_aligned(uint32_t size) {
    return kmalloc_impl(size, true, nullptr);
}

uint32_t kernel::kmalloc_phys(uint32_t size, uint32_t* phys) {
    return kmalloc_impl(size, false, phys);
}

uint32_t kernel::kmalloc_ap(uint32_t size, uint32_t* phys) {
    return kmalloc_impl(size, true, phys);
}

uint32_t kernel::kmalloc(uint32_t size) {
    return kmalloc_impl(size, false, nullptr);
}

void kernel::disable_kmalloc() {
    kmalloc::enabled = false;
}
