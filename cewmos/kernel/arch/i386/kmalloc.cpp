#include <kernel/kmalloc.h>
#include <kernel/panic.h>

extern "C" uint32_t _kernel_end;
uint32_t placement_address {(uint32_t)&_kernel_end};
uint32_t mem_beginning {(uint32_t)&_kernel_end};

bool kmalloc::enabled = true;

struct kmalloc_meta {
    uint32_t size;
    kmalloc_meta* next;
    kmalloc_meta* last;
} __attribute__((packed));

kmalloc_meta* free_list_head {nullptr}; // head will always be the lowest memory chunk available in memory

kmalloc_meta* last_header_location = (kmalloc_meta*)mem_beginning;

// FUNCTIONS RELATED TO FREEING

static void insert_header(kmalloc_meta* header) {
    kmalloc_meta* iter {free_list_head};
    if(!iter) {
        header->last = nullptr;
        header->next = nullptr;
        free_list_head = header;
    }
    while((uint32_t)iter < (uint32_t)header) {
        if(!iter->next) //break loop if it's last header in list
            break;
        iter = iter->next;
    }
    if(iter->last)
        iter->last->next = header //if iter isn't head, connect previous with header
    else
        free_list_head = header //otherwise make header the head
    header->last = iter->last;
    iter->last = header;
    header->next = iter;
}

static void remove_header(kmalloc_meta* header) {
    // remove header from link
    if(header->last)
        header->last->next = header->next;
    else
        free_list_head = header->next;
    header->next->last = header->last;

    // reset header's next and last
    header->next = nullptr;
    header->last = nullptr;
}

static uint32_t free_count {0};

void kmalloc_free(void* ptr) {
    kmalloc_meta* header = (kmalloc_meta*) ((uint32_t)ptr - sizeof(kmalloc_meta));
    ++free_count;
    if(free_count >= 15)
        compress_memory();
    insert_header(header);
}

uint32_t find_header_alloc_spot(size_t size) {
    kmalloc_meta* iter = free_list_head;
    if(!iter) {
        return placement_address;
    }
    while(iter->size < size) {
        iter = iter->next;
        if(!iter) {
            return placement_address;
        }
    }
    //if we've found a suitable spot, remove freed header from list and return its location
    remove_header(iter);
    return (uint32_t)iter;
}

//

static uint32_t kmalloc_impl(uint32_t size, bool aligned, uint32_t* phys) {
    if(!kmalloc::enabled) {
        kernel::panic::panic("kmalloc is disabled", "", true);
    }

    if(aligned && (placement_address & 0xfffff000)) {
        //if address isn't page aligned align it
        placement_address &= 0xfffff000; //set to current page
        placement_address += 0x1000; //advance one page
    }

    size_t alloc_spot = find_header_alloc_spot(size);
    kmalloc_meta* header = (kmalloc_meta*) alloc_spot;
    header->size = size;
    header->next = (kmalloc_meta*)(placement_address + sizeof(kmalloc_meta) + size);
    if((uint32_t)header == mem_beginning) {
        header->last = nullptr;
    }
    else header->last = last_header_location;

    if(alloc_spot == placement_address)
        last_header_location = (uint32_t) header;

    placement_address += sizeof(kmalloc_meta);

    if(phys) {
        *phys = placement_address;
    }

    uint32_t tmp = placement_address;
    placement_address += size;

    return tmp;
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
