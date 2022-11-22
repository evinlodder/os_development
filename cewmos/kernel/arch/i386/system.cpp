#include <kernel/system.h>

EXTERN void kernel::system::enable_interrupts(bool b) {
    if(b) {
        asm("sti");
    } else {
        asm("cli");
    }
}
