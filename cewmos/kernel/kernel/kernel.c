#include <stdio.h>

#include <kernel/tty.h>

#ifdef __cplusplus
extern "C"
#endif
void kernel_main(void) {
    terminal_initialize();
	printf("Hello, kernel World!\n");
}
