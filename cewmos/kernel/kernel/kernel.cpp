#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>

EXTERN void testint() {
    printf("\nTEST INTERRUPT CALLED\n");
}
EXTERN void kernel_main(VOID) {

	printf("Hello, kernel World!\nI love coding <3");
    asm("int $10");
}

EXTERN void system_setup(VOID) {
    terminal_initialize();
    //set up IDT
    kernel::system::enable_interrupts(false);
    kernel::pic::remap_pic(0x20, 0x28);
    kernel::pic::mask_irq(ALL);

    kernel::interrupts::load_interrupts();

    kernel::idt::set_interrupt(48, kernel::interrupts::_int32, kernel::idt::get_cs(), PRESENT | RING_U | INT_GATE_32);

    kernel::idt::load_idt();

    kernel::system::enable_interrupts(true);
}
