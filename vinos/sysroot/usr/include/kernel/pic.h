#ifndef PIC_H
#define PIC_H
#include <kernel/system.h>

//IRQ macros
#define ALL        0xFF
#define TIMER      0
#define KEYBOARD   1
#define CASCADE    2
#define COM2_4     3
#define COM1_3     4
#define LPT        5
#define FLOPPY     6
#define PARALLEL_1 7
#define RTC        8
#define ACPI       9
#define FREE10     10
#define FREE11     11
#define PS2MOUSE   12
#define CPUCO      13
#define IDE_1       14
#define IDE_2       15
//

//PIC macros
#define MASTER     0x20
#define MASTERDATA 0x21
#define SLAVE      0xA0
#define SLAVEDATA  0xA1
#define EOI        0x20
//


//ICW1 and ICW4 control words are the only ones we have to worry about
#define ICW1_INIT    0x10               // required for PIC initialisation
#define ICW1_EDGE    0x08               // edge triggered IRQs
#define ICW1_SINGLE  0x02               // only MASTER (not cascaded)
#define	ICW1_ICW4    0x01               // there IS an ICW4 control word

#define ICW4_SFNM    0x10               // Special Fully Nested Mode
#define ICW4_BUFFER  0x08               // Buffered Mode
#define ICW4_MASTER  0x04               // this is the Master PIC
#define ICW4_AEOI    0x02               // Auto EOI
#define ICW4_8086    0x01               // 80/86 Mode

#ifdef __cplusplus
namespace kernel { namespace pic {
#endif

EXTERN void remap_pic(uint32_t pic1, uint32_t pic2);
EXTERN void mask_irq(byte irq);
EXTERN void unmask_irq(byte irq);
EXTERN void send_eoi(byte irq);

#ifdef __cplusplus
}}
#endif

#endif //PIC_H
