#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <dominos/map.h>
#include <initializer_list>
#include "multiboot.h"


extern "C" uint32_t _kernel_start;
extern "C" uint32_t _kernel_end;

extern "C" uint32_t _new_kernel_start;
EXTERN void test(VOID){}
EXTERN void setup_mem(multiboot_info_t* mbd, uint32_t magic) {
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
        printf("invalid memory map!");
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
    char* first = (char*) kernel::kmalloc(5);
    printf("first location: 0x%x\n", (uint32_t)first);
    char* second = (char*) kernel::kmalloc(5);
    char* third = (char*) kernel::kmalloc(5);
    char* fourth = (char*) kernel::kmalloc(5);
    char* fifth = (char*) kernel::kmalloc(5);
    char* sixth = (char*) kernel::kmalloc(5);
    char* seventh = (char*) kernel::kmalloc(5);
    char* eighth = (char*) kernel::kmalloc(5);
    char* ninth = (char*) kernel::kmalloc(5);
    char* tenth = (char*) kernel::kmalloc(5);
    char* eleventh = (char*) kernel::kmalloc(5);
    char* twelfth = (char*) kernel::kmalloc(5);
    char* thirteenth = (char*) kernel::kmalloc(5);
    char* fourteenth = (char*) kernel::kmalloc(5);
    char* fifteenth = (char*) kernel::kmalloc(5);
    printf("fifteenth location: 0x%x\n", (uint32_t)fifteenth);

    kernel::kfree(first);
    kernel::kfree(second);
    kernel::kfree(third);
    kernel::kfree(fourth);
    kernel::kfree(fifth);
    kernel::kfree(sixth);
    kernel::kfree(seventh);
    kernel::kfree(eighth);
    kernel::kfree(ninth);
    kernel::kfree(tenth);
    kernel::kfree(eleventh);
    kernel::kfree(twelfth);
    kernel::kfree(thirteenth);
    kernel::kfree(fourteenth);
    kernel::kfree(fifteenth);
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


