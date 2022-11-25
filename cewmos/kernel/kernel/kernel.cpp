#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>


EXTERN void kernel_main(VOID) {

	printf("starting 15 second timer...\n");
    kernel::pit::sleep_s(15);
    printf("15 seconds over!");

}

EXTERN void system_setup(VOID) {
    terminal_initialize();
    //set up IDT
    kernel::system::enable_interrupts(false);
    kernel::pic::remap_pic(0x20, 0x28);
    kernel::pic::mask_irq(ALL);
    kernel::pic::unmask_irq(TIMER);

    kernel::interrupts::load_interrupts();

    kernel::pit::timer_install(100);

    kernel::idt::load_idt();

    kernel::system::enable_interrupts(true);
}
