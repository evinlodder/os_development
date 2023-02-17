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

EXTERN void setup_mem(multiboot_info_t* mbd, uint32_t magic, uint32_t* pd) {
    //check magic
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
    printf("magic: 0x%x", magic);
}

EXTERN void kernel_main(VOID) {


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


