#include <kernel/hio.h>

// Outputs byte to hardware port
inline void kernel::hio::out_port_b(uint32_t port, byte value) {
    asm volatile("outb %%al,%%dx"::"d" (port), "a" (value));
}

// Outputs word to hardware port
inline void kernel::hio::out_port_w(uint32_t port, uint32_t value) {
    asm volatile("outw %%ax,%%dx"::"d" (port), "a" (value));
}

// gets byte from hardware port
inline byte kernel::hio::in_port_b(uint32_t port) {
    byte value{};
    asm volatile("inb %w1,%b0" : "=a"(value) : "d"(port));
    return value;
}
