#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <dominos/map.h>
#include <initializer_list>
#include "multiboot.h"


extern "C" uint32_t _kernel_start;
extern "C" uint32_t _kernel_end;

extern "C" uint32_t _new_kernel_start;

EXTERN void kernel_main(VOID) {
   
    char* test_string = (char*) kernel::kmalloc(sizeof(char) * 4);
    test_string = "nut";
    printf(test_string);


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


