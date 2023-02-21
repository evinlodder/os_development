#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <dominos/map.h>
#include <initializer_list>
#include "multiboot.h"


extern "C" uint32_t _kernel_start;
extern "C" uint32_t _kernel_end;

extern "C" uint32_t _new_kernel_start;
extern "C" uint32_t* kernel_addr_offset;

static void print_mbinfo(multiboot_info_t* mbd) {
    printf("flags: %b\n", mbd->flags);
    printf("mem_lower: 0x%x\n", mbd->mem_lower);
    printf("mem_upper: 0x%x\n", mbd->mem_upper);
    printf("ram size: %d MB\n", mbd->mem_upper / 1024 + 2);
    printf("paging size: %d\n", (mbd->mem_upper * 1024) / 4096 + 30000);
    printf("mods_count: %d\n", mbd->mods_count);
    printf("mods_addr: 0x%x\n", mbd->mods_addr);
    printf("mmap_length: %d\n", mbd->mmap_length);
    printf("mmap_addr: 0x%x\n", mbd->mmap_addr);
}

EXTERN void setup_mem(multiboot_info_t* mbd, uint32_t magic, uint32_t* pd, uint32_t* pt_one) {
    //check magic
    printf("pd: 0x%x\n", (uint32_t)pd);
    printf("pt_one: 0x%x\n", (uint32_t)pt_one);
    printf("pd[768]: 0b%b\n", (uint32_t)pd[768]);
    printf("pt_one[1022]: 0b%b\n", (uint32_t)pt_one[1022]);
    printf("pd[768] addr: 0x%x\n", ((uint32_t)pd[768]) & 0xFFFFF000);
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("magic is wrong!\n");
        printf("magic: 0x%x", magic);
        while(true) {
            asm("cli");
            asm("hlt");
        }
    }

    //check mbd
    if(!((mbd->flags >> 6) & 0x1)) {
        printf("invalid memory map!\n");
        printf("flags:       0x%x\n", mbd->flags);
        while(true) {
            asm("cli");
            asm("hlt");
        }
    }
    printf("valid memory map and magic number!\n");
    printf("mbd location: 0x%x\n", mbd);
    print_mbinfo(mbd);
    printf("\n");
    //while(1) asm("hlt");
    mbd->mmap_addr = (uint32_t)mbd + (mbd->mmap_addr - 0x10000);
    for(size_t i{}; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
        auto mmap = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
        uint64_t addr = ((uint64_t)mmap->addr_high << 32) + mmap->addr_low;
        uint64_t length = ((uint64_t)mmap->len_high << 32) + mmap->len_low;
        printf("start addr: 0x%x | ", addr);
        printf("length: 0x%x | ", length);
        printf("size: 0x%x | ", mmap->size);
        printf("type: ");
        switch(mmap->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                printf("AVAILABLE!\n");
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                printf("reserved\n");
                break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                printf("ACPI reclaimable\n");
                break;
            case MULTIBOOT_MEMORY_NVS:
                printf("nvs\n");
                break;
            case MULTIBOOT_MEMORY_BADRAM:
                printf("bad ram\n");
                break;
            default:
                break;
        }
    }
}

EXTERN void kernel_main(VOID) {
    printf("new kernel start: %x", &_new_kernel_start);

}
EXTERN void system_setup(VOID) {
    terminal_initialize();
    //set up IDT
    kernel::system::enable_interrupts(false);
    kernel::pic::remap_pic(0x20, 0x28);
    kernel::pic::mask_irq(ALL);
    kernel::pic::unmask_irq(TIMER);
    kernel::pic::unmask_irq(KEYBOARD);

    kernel::interrupts::load_interrupts();

    kernel::pit::timer_install(100);
    kernel::keyboard::install_us_qwerty_board();

    kernel::idt::load_idt();

    kernel::system::enable_interrupts(true);
}


