#ifndef PIT_H
#define PIT_H

#include <kernel/hio.h>
#include <kernel/sysdefs.h>

//pit chip IO ports
#define PIT_CHANNEL_0   0x40
#define PIT_CHANNEL_1   0x41
#define PIT_CHANNEL_2   0x42
#define PIT_COMMAND_REG 0x43

//bit 0 in mode/command register
#define BINARY 0
#define BCD    1

//bits 1-3 - operating mode
#define MODE_0     0      //interrupt on terminal count
#define MODE_1     0b0010 //hardware re-triggerable one-shot
#define MODE_2     0b0100 //rate generator
#define MODE_3     0b0110 //square wave generator
#define MODE_4     0b1000 //software triggered strobe
#define MODE_5     0b1010 //hardware triggered strobe
#define MODE_2_REP 0b1100 //same as mode 2
#define MODE_3_REP 0b1110 //same as mode 3

//bits 4 and 5 - access mode
#define LATCH_COUNT_COMMAND 0
#define A_LOBYTE_ONLY       0b010000
#define A_HIBYTE_ONLY       0b100000
#define LOBYTE_HIBYTE       0b110000

//bits 6 and 7 - channel selection
#define CHANNEL_0_SELECT 0
#define CHANNEL_1_SELECT 0b01000000
#define CHANNEL_2_SELECT 0b10000000
#define CHANNEL_3_SELECT 0b11000000

#ifdef __cplusplus
namespace kernel { namespace pit {
#endif

void timer_phase(int hz);
void timer_handler(VOID);
void sleep_t(int ticks);
void sleep_ms(int ms);
void sleep_s(int s);
void timer_install(int hz);

#ifdef __cplusplus
}}
#endif

#endif //PIT_H
