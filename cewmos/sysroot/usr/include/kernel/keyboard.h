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

/* structure of keyboard manager flags - 1 means on, 0 means off
 * bit 0 - always ignore (was pressed bit, but structure has changed)
 * bit 1 - shift
 * bit 2 - control
 * bit 3 - alt
 *
 * bit 4 - caps lock
 * bit 5 - nums lock
 * bit 6 - scroll lock
 *
 * bit 7 - always zero
 */

class keyboard_manager {
public:
    //only works with keys that print text
    void handle_irq(uint8_t scancode);
private:
    void print_character(char c);
};

static keyboard_manager key_manager{};

void irq_handler(VOID);
void install_us_qwerty_board(VOID);
#ifdef __cplusplus
}}
#endif

#endif //KEYBOARD_H
