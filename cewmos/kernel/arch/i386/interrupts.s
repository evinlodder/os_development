.global _int00
_int00:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 .extern int_00
 call int_00 #DE divide by zero exception

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int01
_int01:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_01

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int02
_int02:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_02

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int03
_int03:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_03

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int04
_int04:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_04

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int05
_int05:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_05

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int06
_int06:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_06

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int07
_int07:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_07

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int08
_int08:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_08

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int09
_int09:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_09

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int10
_int10:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_10

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int11
_int11:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_11

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int12
_int12:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_12

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int13
_int13:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_13

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int14
_int14:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 mov %cr2, %eax
 push %eax
 # do what you want to here :)
 call int_14

 pop %eax
 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

#SKIP 15 because it is intel reserved

.global _int16
_int16:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_16

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int17
_int17:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_17

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int18
_int18:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_18

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int19
_int19:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_19

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int20
_int20:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_20

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _int21
_int21:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $data_segment, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_21

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

# Exceptions 22-31 are all intel reserved

 #
 # END OF EXCEPTION INTERRUPTS. 32-255 CAN BE WHATEVER YOU WANT
 #

 # INTERRUPTS 32-47 ARE IRQs 0-15
.global _irq00
_irq00:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_00

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq01
_irq01:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_01

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq02
_irq02:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_02

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq03
_irq03:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_03

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq04
_irq04:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_04

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq05
_irq05:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_05

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq06
_irq06:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_06

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq07
_irq07:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_07

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq08
_irq08:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_08

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq09
_irq09:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_09

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq10
_irq10:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_10

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq11
_irq11:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_11

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq12
_irq12:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_12

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq13
_irq13:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_13

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq14
_irq14:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_14

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

.global _irq15
_irq15:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call irq_15

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret

# INTERRUPTS 48-255 ARE FREE

.global _int48
_int48:
 pusha
 push %gs
 push %fs
 push %es
 push %ds
 mov $0x10, %eax
 mov %eax, %es
 mov %eax, %ds
 cld

 # do what you want to here :)
 call int_48

 pop %ds
 pop %es
 pop %fs
 pop %gs
 popa
 iret
