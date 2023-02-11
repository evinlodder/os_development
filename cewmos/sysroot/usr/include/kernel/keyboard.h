#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <kernel/sysdefs.h>
#include <kernel/ps2.h>

// some #defines to go with the keypress flags - UNUSED AS OF RIGHT NOW
//#define PRESSED             0b1
//#define SHIFT_PRESSED       0b10
//#define CONTROL_PRESSED     0b100
//#define ALT_PRESSED         0b1000
//#define CAPS_LOCK_TOGGLED   0b10000
//#define NUMS_LOCK_TOGGLED   0b100000
//#define SCROLL_LOCK_TOGGLED 0b1000000

#ifdef __cplusplus
namespace kernel { namespace keyboard {
#endif

struct keycode_packet {
    uint8_t keycode; //upper 3 bits - row, bottom 5 bits - column
    uint8_t flags; // look below
};

/* structure of keyboard manager flags - 1 means on, 0 means off
 * bit 0 - shift
 * bit 1 - control
 * bit 2 - alt
 *
 * bit 3 - caps lock
 * bit 4 - nums lock
 * bit 5 - scroll lock
 *
 * bit 6 - pressed
 * bit 7 - always zero
 */

class keyboard_manager {
public:
    //only works with keys that print text
    void handle_irq(uint8_t scancode);
    //ALL OF THESE ARE 16 BITS INSTEAD OF 8 BITS BECAUSE OF HOW SPECIAL CODES ARE HANDLED
    // SOME CODES, LIKE RIGHT CONTROL ON USQWERTY
    void set_special_scancodes(uint16_t lshift,
                               uint16_t rshift,
                               uint16_t rcontrol,
                               uint16_t lcontrol,
                               uint16_t lalt,
                               uint16_t ralt,
                               uint16_t capslock,
                               uint16_t nlock,
                               uint16_t slock);
    void set_special_scancodes(uint16_t scodes[9]);
    keycode_packet current_packet {0, 0}; //make interrupt to read this
private:
    void print_character(char c);
    uint16_t left_shift,
            right_shift,
            left_control,
            right_control,
            left_alt,
            right_alt,
            caps_lock,
            num_lock,
            scroll_lock;
};

static keyboard_manager key_manager{};

void irq_handler(VOID);
void install_us_qwerty_board(VOID);
#ifdef __cplusplus
}}
#endif

#endif //KEYBOARD_H
