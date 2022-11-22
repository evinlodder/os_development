#include <kernel/panic.h>
#include <stdio.h>
#include <kernel/hio.h>
#include <kernel/pic.h>

void kernel::panic::panic(const char* message, const char* code, bool halt) {
    clear_screen();
    printf("<SYSTEM ERROR>\n");
    printf("A %s error has occured.\n", (halt ? "fatal" : "non-fatal"));
    printf("%s %s", code, message);

    if(halt) {
        printf("System halted.");
        asm("cli\n");
        asm("hlt");
    } else {
        printf("\nPress any key to continue.");
    }
    kernel::hio::out_port_b(MASTER, EOI);
}

