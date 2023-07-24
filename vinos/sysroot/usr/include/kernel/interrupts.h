#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <kernel/sysdefs.h>

#ifdef __cplusplus
namespace kernel { namespace interrupts {
#endif

struct registers_t{
   uint16_t ds, es, fs, gs; /* data segment selector */
   uint16_t di, si, bp, sp, bx, dx, cx, ax; /* pushed by pusha. */
};

EXTERN void _int00(VOID);
EXTERN void _int01(VOID);
EXTERN void _int02(VOID);
EXTERN void _int03(VOID);
EXTERN void _int04(VOID);
EXTERN void _int05(VOID);
EXTERN void _int06(VOID);
EXTERN void _int07(VOID);
EXTERN void _int08(VOID);
EXTERN void _int09(VOID);
EXTERN void _int10(VOID);
EXTERN void _int11(VOID);
EXTERN void _int12(VOID);
EXTERN void _int13(VOID);
EXTERN void _int14(VOID);
EXTERN void _int16(VOID);
EXTERN void _int17(VOID);
EXTERN void _int18(VOID);
EXTERN void _int19(VOID);
EXTERN void _int20(VOID);
EXTERN void _int21(VOID);

EXTERN void _irq00(VOID);
EXTERN void _irq01(VOID);
EXTERN void _irq02(VOID);
EXTERN void _irq03(VOID);
EXTERN void _irq04(VOID);
EXTERN void _irq05(VOID);
EXTERN void _irq06(VOID);
EXTERN void _irq07(VOID);
EXTERN void _irq08(VOID);
EXTERN void _irq09(VOID);
EXTERN void _irq10(VOID);
EXTERN void _irq11(VOID);
EXTERN void _irq12(VOID);
EXTERN void _irq13(VOID);
EXTERN void _irq14(VOID);
EXTERN void _irq15(VOID);

// USER-DEFINED INTERRUPTS
EXTERN void _int48(VOID);


EXTERN void load_interrupts(VOID);
EXTERN void int_00(VOID);
EXTERN void int_01(VOID);
EXTERN void int_02(VOID);
EXTERN void int_03(VOID);
EXTERN void int_04(VOID);
EXTERN void int_05(VOID);
EXTERN void int_06(VOID);
EXTERN void int_07(VOID);
EXTERN void int_08(VOID);
EXTERN void int_09(VOID);
EXTERN void int_10(VOID);
EXTERN void int_11(VOID);
EXTERN void int_12(VOID);
EXTERN void int_13(VOID);
EXTERN void int_14(uint32_t cr2, registers_t regs, uint32_t err_code);
EXTERN void int_16(VOID);
EXTERN void int_17(VOID);
EXTERN void int_18(VOID);
EXTERN void int_19(VOID);
EXTERN void int_20(VOID);
EXTERN void int_21(VOID);

EXTERN void irq_00(VOID);
EXTERN void irq_01(VOID);
EXTERN void irq_02(VOID);
EXTERN void irq_03(VOID);
EXTERN void irq_04(VOID);
EXTERN void irq_05(VOID);
EXTERN void irq_06(VOID);
EXTERN void irq_07(VOID);
EXTERN void irq_08(VOID);
EXTERN void irq_09(VOID);
EXTERN void irq_10(VOID);
EXTERN void irq_11(VOID);
EXTERN void irq_12(VOID);
EXTERN void irq_13(VOID);
EXTERN void irq_14(VOID);
EXTERN void irq_15(VOID);

//USER-DEFINED INTERRUPT HANDLERS
EXTERN void int_48(VOID);
#ifdef __cplusplus
}}
#endif


#endif //INTERRUPTS_H
