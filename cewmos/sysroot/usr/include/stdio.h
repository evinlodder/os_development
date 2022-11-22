#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict__, ...);
int putchar(int);
int puts(const char*);
void clear_screen(void);

#ifdef __cplusplus
}
#endif

#endif
