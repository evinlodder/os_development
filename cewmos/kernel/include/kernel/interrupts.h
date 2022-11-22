#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <kernel/sysdefs.h>

#ifdef __cplusplus
namespace kernel { namespace interrupts {
#endif

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
EXTERN void _int32(VOID);

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
EXTERN void int_14(uint32_t cr2);
EXTERN void int_16(VOID);
EXTERN void int_17(VOID);
EXTERN void int_18(VOID);
EXTERN void int_19(VOID);
EXTERN void int_20(VOID);
EXTERN void int_21(VOID);
#ifdef __cplusplus
}}
#endif


#endif //INTERRUPTS_H
