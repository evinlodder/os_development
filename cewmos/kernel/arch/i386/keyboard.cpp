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
static bool control_down = false;
static bool caps_lock = false;
void kernel::keyboard::keyboard_manager::print_character(char c) {
    if(::control_down) //will add functionality if necessary later
        return;
    bool capital{};
    if(::left_shift_down || ::right_shift_down) {
        capital = true;
    }
    capital ^= ::caps_lock;
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

void kernel::keyboard::keyboard_manager::handle_irq(uint8_t scancode) {
    if(scancode > 0x80) {
        //if key released
         switch(scancode) {
             case 0xAA: //lshift down
                 ::left_shift_down = false;
                 break;
             case 0xB6:
                 ::right_shift_down = false;
                 break;
             case 0x9D:
                 ::control_down = false;
                 break;
         }
    }
    else {
        switch(scancode) {
            case 0x2A:
                ::left_shift_down = true;
                break;
            case 0x36:
                ::right_shift_down = true;
                break;
            case 0x3A:
                ::caps_lock = !caps_lock;
                break;
            case 0x1D:
                ::control_down = true;
                break;
            default:
                print_character(keycodes[scancode]);
                break;
        }
    }
}

void kernel::keyboard::irq_handler() {
    using namespace kernel::hio;
    byte status = in_port_b(STATUS_REGISTER);
    byte scancode = in_port_b(DATA_PORT);
    kernel::keyboard::key_manager.handle_irq(scancode);
}

void kernel::keyboard::install_us_qwerty_board() {

}


