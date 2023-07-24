#ifndef IDT_H
#define IDT_H

#include <kernel/sysdefs.h>
#define TASK_GATE    0x5
#define INT_GATE_16  0x6
#define TRAP_GATE_16 0x7
#define INT_GATE_32  0xE
#define TRAP_GATE_32 0xF

#define PRESENT 0b10000000

#define RING_K  0
#define RING_1  0b0100000
#define RING_2  0b1000000
#define RING_U  0b1100000

#define CODE_SEGMENT get_cs()

#ifdef __cplusplus
namespace kernel { namespace idt {
#endif

struct interrupt_descriptor {
    word low_base;
    word selector;
    byte zero;
    byte type_attributes;
    word high_base;
} __attribute__((packed));

struct idtr {
    word limit;
    uint32_t base;
} __attribute__((packed));

EXTERN void set_interrupt(byte num, void (*handler)(), word selector, byte flags);
EXTERN void load_idt(VOID);
word get_cs(VOID);
EXTERN void l_idt(VOID);

#ifdef __cplusplus
}}
#endif

#endif //IDT_H
