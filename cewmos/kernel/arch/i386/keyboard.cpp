#include <kernel/keyboard.h>
#include <stdio.h>


// ALL OF THIS IS WIP
static const char keycodes[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static bool right_shift_down = false;
static bool left_shift_down = false;

static bool left_control_down = false;
static bool right_control_down = false;

static bool left_alt_down = false;
static bool right_alt_down = false;

static bool caps_lock_down = false;
static bool nums_lock_down = false;
static bool scroll_lock_down = false;


void kernel::keyboard::keyboard_manager::print_character(char c) {
    if(::left_control_down || ::right_control_down) //will add functionality if necessary later
        return;
    bool capital{};
    if(::left_shift_down || ::right_shift_down) {
        capital = true;
    }
    capital ^= ::caps_lock_down;
    char out[2] = { c, '\0' };
    if(capital && (c >= 'a' && c <= 'z')) {
        out[0] -= 32;
    }
    else if(capital) {
        switch(c) {
            case '`':
                out[0] = '~';
                break;
            case '-':
                out[0] = '_';
                break;
            case '=':
                out[0] = '+';
                break;
            case '[':
                out[0] = '{';
                break;
            case ']':
                out[0] = '}';
                break;
            case '\\':
                out[0] = '|';
                break;
            case ';':
                out[0] = ':';
                break;
            case '\'':
                out[0] = '\"';
                break;
            case ',':
                out[0] = '<';
                break;
            case '.':
                out[0] = '>';
                break;
            case '/':
                out[0] = '?';
                break;
            case '1':
                out[0] = '!';
                break;
            case '2':
                out[0] = '@';
                break;
            case '3':
                out[0] = '#';
                break;
            case '4':
                out[0] = '$';
                break;
            case '5':
                out[0] = '%';
                break;
            case '6':
                out[0] = '^';
                break;
            case '7':
                out[0] = '&';
                break;
            case '8':
                out[0] = '*';
                break;
            case '9':
                out[0] = '(';
                break;
            case '0':
                out[0] = ')';
                break;
        }
    }
    printf(out);
}


static inline void handle_special(bool check, uint8_t bit) {
    using namespace kernel::keyboard;
    if(!check) {
        key_manager.current_packet.flags &= ~(1 << bit);
    } else {
        key_manager.current_packet.flags |= (1 << bit);
    }
}

void kernel::keyboard::keyboard_manager::handle_irq(uint8_t scancode) {
    if(scancode > 0x80) {
        //if key released
        if(scancode == (left_shift + 0x80)) {
            ::left_shift_down = false;
            handle_special(::right_shift_down, 0);
        }
        else if(scancode == (right_shift + 0x80)) {
            ::right_shift_down = false;
            handle_special(::left_shift_down, 0);
        }
        else if(scancode == (left_control + 0x80)) {
            ::left_control_down = false;
            handle_special(::right_control_down, 1);
        }
        else if(scancode == (right_control + 0x80)) {
            ::right_control_down = false;
            handle_special(::left_control_down, 1);
        }
        else if(scancode == (left_alt + 0x80)) {
            ::left_alt_down = false;
            handle_special(::right_alt_down, 2);
        }
        else if(scancode == (right_alt + 0x80)) {
            ::right_alt_down = false;
            handle_special(::left_alt_down, 2);
        }
        else if(scancode == (caps_lock + 0x80)) {
            //as of right now, you don't need to do anything
        }
        else if(scancode == (num_lock + 0x80)) {
            //as of right now, you don't need to do anything
        }
        else if(scancode == (scroll_lock + 0x80)) {
            //as of right now, you don't need to do anything
        }
        current_packet.flags &= 0b00111111; //set pressed flag to false
    }
    else {
        if(scancode == (left_shift)) {
            ::left_shift_down = true;
            current_packet.flags |= (1 << 0);
        }
        else if(scancode == (right_shift)) {
            ::right_shift_down = true;
            current_packet.flags |= (1 << 0);
        }
        else if(scancode == (left_control)) {
            ::left_control_down = true;
            current_packet.flags |= (1 << 1);
        }
        else if(scancode == (right_control)) {
            ::right_control_down = true;
            current_packet.flags |= (1 << 1);
        }
        else if(scancode == (left_alt)) {
            ::left_alt_down = true;
            current_packet.flags |= (1 << 2);
        }
        else if(scancode == (right_alt)) {
            ::right_alt_down = true;
            current_packet.flags |= (1 << 2);
        }
        else if(scancode == (caps_lock)) {
            ::caps_lock_down = !::caps_lock_down;
            handle_special(::caps_lock_down, 3);
        }
        else if(scancode == (num_lock)) {
            ::nums_lock_down = !::nums_lock_down;
            handle_special(::nums_lock_down, 4)
        }
        else if(scancode == (scroll_lock)) {
            ::scroll_lock_down = !::scroll_lock_down;
            handle_special(::scroll_lock_down, 5);
        }
        current_packet.flags |= 0b01000000;
    }
}

void kernel::keyboard::irq_handler() {
    using namespace kernel::hio;
    byte status = in_port_b(STATUS_REGISTER);
    byte scancode = in_port_b(DATA_PORT);
    kernel::keyboard::key_manager.handle_irq(scancode);
}

void kernel::keyboard::keyboard_manager::set_special_scancodes(
                               uint16_t lshift,
                               uint16_t rshift,
                               uint16_t rcontrol,
                               uint16_t lcontrol,
                               uint16_t lalt,
                               uint16_t ralt,
                               uint16_t capslock,
                               uint16_t nlock,
                               uint16_t slock) {
    left_shift = lshift;
    right_shift = rshift;
    right_control = rcontrol;
    left_control = lcontrol;
    left_alt = lalt;
    right_alt = ralt;
    caps_lock = capslock;
    num_lock = nlock;
    scroll_lock = slock;
}

void kernel::keyboard::keyboard_manager::set_special_scancodes(uint16_t scodes[9]) {
    left_shift = scodes[0];
    right_shift = scodes[1];
    right_control = scodes[2];
    left_control = scodes[3];
    left_alt = scodes[4];
    right_alt = scodes[5];
    caps_lock = scodes[6];
    num_lock = scodes[7];
    scroll_lock = scodes[8];
}

static uint16_t usqwerty_special_codes[9] {
    0x2A,
    0x36,
    0xE0 + 0x1D,
    0x1D,
    0x38,
    0xE0 + 0x38,
    0x3A,
    0x45,
    0x46
};

void kernel::keyboard::install_us_qwerty_board() {
    kernel::keyboard::key_manager.set_special_scancodes(usqwerty_special_codes);
}


