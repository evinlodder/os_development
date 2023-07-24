#include <kernel/idt.h>
#include <kernel/interrupts.h>
kernel::idt::interrupt_descriptor idt[256]{};
kernel::idt::idtr idt_des{};


EXTERN void kernel::idt::set_interrupt(byte num, void (*handler)(), word selector, byte flags) {
    uint32_t base = (uint32_t)(handler);

    ::idt[num].low_base = (base & 0xFFFF);
    ::idt[num].selector = selector;
    ::idt[num].zero = 0;
    ::idt[num].type_attributes = flags;
    ::idt[num].high_base = (base >> 16);
}

EXTERN void kernel::idt::load_idt(VOID) {
    //set up IDT descriptor
    ::idt_des.limit = (256 * sizeof(kernel::idt::interrupt_descriptor)) - 1;
    ::idt_des.base = (uint32_t)::idt;

    //lidt (idt_des)
    kernel::idt::l_idt();
}

word kernel::idt::get_cs(VOID) {
    word code_segment = 0x08;
    asm volatile("movw %%cs,%0" :"=g"(code_segment));
    return code_segment;
}
