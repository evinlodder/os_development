#ifndef PANIC_H
#define PANIC_H
#include <kernel/sysdefs.h>

#ifdef __cplusplus
namespace kernel { namespace panic {
#endif //__cplusplus


void panic(const char* message, const char* code, bool halt);


#ifdef __cplusplus
}}
#endif //__cplusplus

#endif //PANIC_H
