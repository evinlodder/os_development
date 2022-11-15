#ifndef SYSTEM_H
#define SYSTEM_H

#include <kernel/sysdefs.h>

#ifdef __cplusplus
namespace kernel { namespace system {
#endif

void enable_interrupts(bool b);

#ifdef __cplusplus
}}
#endif

#endif //SYSTEM_H
