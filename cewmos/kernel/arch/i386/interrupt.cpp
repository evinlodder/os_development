#include <kernel/system.h>

void kernel::system::enable_interrupts(bool b) {
    if(b) {
        asm("sti");
    } else {
        asm("cli");
    }
}
