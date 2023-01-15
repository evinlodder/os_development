#ifndef SYSTEM_H
#define SYSTEM_H

#include <kernel/sysdefs.h>
#include <kernel/idt.h>
#include <kernel/panic.h>
#include <kernel/hio.h>
#include <kernel/interrupts.h>
#include <kernel/adr.h>
#include <kernel/gdt.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/keyboard.h>
#include <kernel/kmalloc.h>

#ifdef __cplusplus
namespace kernel { namespace system {
#endif

EXTERN void enable_interrupts(bool b);

#ifdef __cplusplus
}}
#endif

#endif //SYSTEM_H
