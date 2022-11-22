#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#ifdef __cplusplus
#define PUB extern "C"
#else
#define PUB
#endif
PUB void terminal_initialize(void);
PUB void terminal_putchar(char c);
PUB void terminal_write(const char* data, size_t size);
PUB void terminal_writestring(const char* data);
PUB void cls(void); 

#endif
