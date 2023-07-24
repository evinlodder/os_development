#ifndef PS2_H
#define PS2_H

#include <kernel/sysdefs.h>
#include <kernel/hio.h>

#define DATA_PORT        0x60
#define STATUS_REGISTER  0x64
#define COMMAND_REGISTER 0x64

//status register bits
//0 - output buffer status, must be set before reading from data port
#define OUTPUT_BUFFER_EMPTY 0
#define OUTPUT_BUFFER_FULL  1
//1 - input buffer status, must be clear before writing to 0x60 or 0x64
#define INPUT_BUFFER_EMPTY  0
#define INPUT_BUFFER_FULL   0b10
//2 - system flag - meant to be cleared on reset and set by firmware - skip
//
//3 - command/data
#define DATA_FOR_DEVICE     0
#define DATA_FOR_CONTROLLER 0b1000
//4 & 5 - chipset specific, skip
//
//6 - time out error
#define NO_TIMEOUT_ERROR    0
#define TIMEOUT_ERROR       0b1000000
//7 - parity error
#define NO_PARITY_ERROR     0
#define PARITY_ERROR        0b10000000
//

//PS2 controller commands
#define READ_BYTE(x)          0x20 + x
#define WRITE_BYTE(x)         0x60 + x
#define DISABLE_SECOND_PORT   0xA7
#define ENABLE_SECOND_PORT    0xA8
#define TEST_SECOND_PORT      0xA9
#define TEST_CONTROLLER       0xAA
#define TEST_FIRST_PORT       0xAB
#define DUMP                  0xAC
#define DISABLE_FIRST_PORT    0xAD
#define ENABLE_FIRST_PORT     0xAE
#define READ_CONTROLLER_INPUT 0xC0
#define COPY_1                0xC1
#define COPY_2                0xC2
#define READ_CONTROLLER_OUT   0xD0
#define WRITE_CONTROLLER_OUT  0xD1
#define WRITE_TO_FIRST        0xD2
#define WRITE_TO_SECOND       0xD3
#define WRITE_TO_SECOND_INPUT 0xD4
#define PULSE_LINES(x)        0xF0 | x
//
//response bytes
//
#define PORT_TEST_PASSED       0
#define CLOCK_LINE_STUCK_LOW   1
#define CLOCK_LINE_STUCK_HIGH  2
#define DATA_LINE_STUCK_LOW    3
#define DATA_LINE_STUCK_HIGH   4
#define CONTROLLER_TEST_PASSED 0x55
#define CONTROLLER_TEST_FAILED 0xFC
//
//controller configuration byte
//
//bit 0 - first ps2 port
#define ENABLE_FIRST_INTERRUPT  1
#define DISABLE_FIRST_INTERRUPT 0
//bit 1 - second port
#define ENABLE_SECOND_INTERRUPT  0b10
#define DISABLE_SECOND_INTERRUPT 0
//bit 2 - system flag - should always be 1
#define SYSTEM_PASS 0b100
//bit 3 - should always be zero - skip
//bit 4 - first port clock
#define FIRST_CLOCK_ENABLED  0
#define FIRST_CLOCK_DISABLED 0b10000
//bit 5 - second port clock
#define SECOND_CLOCK_ENABLED  0
#define SECOND_CLOCK_DISABLED 0b100000
//bit 6 - first port translation
#define ENABLE_PORT_TRANSLATION  0b1000000
#define DISABLE_PORT_TRANSLATION 0
//bit 7 - mst be zero - skip
//
//controller output port bits have bad documentation, but I will add if I find good information

#ifdef __cplusplus
namespace kernel { namespace ps2 {
#endif



#ifdef __cplusplus
}}
#endif

#endif //PS2_H
