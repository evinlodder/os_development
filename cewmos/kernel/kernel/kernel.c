#include <stdio.h>
#include <kernel/system.h>
#include <kernel/tty.h>

EXTERN void kernel_main(VOID) {
    terminal_initialize();
	printf("Hello, kernel World!\nI love coding <3");
}

EXTERN void system_setup(VOID) {
    //set up IDT

}
