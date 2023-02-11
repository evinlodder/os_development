#include <kernel/panic.h>
#include <stdio.h>
#include <kernel/hio.h>
#include <kernel/pic.h>

void kernel::panic::panic(const char* message, const char* code, bool halt, uint32_t cr2, uint32_t error_code) {
    clear_screen();
    printf("<SYSTEM ERROR>\n");
    if(cr2 != 0) {
        printf("Page fault at 0x%x\n", cr2);
        printf("Error code: 0b%b\n", error_code);
    }
    printf("A %s error has occured.\n", (halt ? "fatal" : "non-fatal"));
    printf("%s %s\n", code, message);

    if(halt) {
        printf("System halted.");
        asm("cli\n");
        asm("hlt");
    } else {
        printf("\nPress any key to continue.");
    }
    kernel::hio::out_port_b(MASTER, EOI);
}

