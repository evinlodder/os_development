#include <kernel/pit.h>
#include <stdio.h>

int timer_ticks{0};

void kernel::pit::timer_phase(int hz) {
    using namespace kernel::hio;
    int divisor = 1193180 / hz;
    out_port_b(PIT_COMMAND_REG, (BINARY | MODE_2 | LOBYTE_HIBYTE | CHANNEL_0_SELECT));
    out_port_b(PIT_CHANNEL_0, (divisor & 0xFF)); //low byte
    out_port_b(PIT_CHANNEL_0, (divisor >> 8));   //high byte
}

int hz{18};

void kernel::pit::timer_handler() {
    ++timer_ticks;
    //printf("\n%s ticks", timer_ticks);
    //test every 18 ticks(approximately 1 second)
    //if(timer_ticks % hz == 0) {
       // printf("\napprox. 1 second has passed");
    // }
}

void kernel::pit::sleep_t(int ticks) {
    unsigned long eticks {timer_ticks + ticks};
    while(timer_ticks < eticks) {
        asm("hlt");
    }
}

void kernel::pit::sleep_s(int s) {
    kernel::pit::sleep_t(s * hz);
}

void kernel::pit::sleep_ms(int ms) {
    kernel::pit::sleep_t((ms / 1000) * (hz));
}

void kernel::pit::timer_install(int hz) {
    ::hz = hz;
    kernel::pit::timer_phase(hz);
}
