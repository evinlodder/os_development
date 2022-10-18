#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//check if compiler thinks you are targeting wrong os
#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif
//this tutorial will only work for 32-bit ix86 targets
#if !defined(__i386__)
#error "This (kernel.h) needs to be compiled with an ix86-elf compiler"
#endif

namespace utility {
    size_t strlen(const char* str) {
        size_t len{};
        while(str[len])
            ++len;
        return len;
    }
}

namespace kernel {
//Hardware text mode color constants
    enum class vga_color {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15,
    };

    static inline uint8_t vga_entry_color(vga_color fg, vga_color bg) {
        return static_cast<uint8_t>(fg) | static_cast<uint8_t>(bg) << 4;
    }

    static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
        return static_cast<uint16_t>(uc) | static_cast<uint16_t>(color) << 8;
    }


    static const size_t VGA_WIDTH {80};
    static const size_t VGA_HEIGHT {25};

    size_t terminal_row{}; //y
    size_t terminal_column{}; //x
    uint8_t terminal_color{};
    uint16_t* terminal_buffer;
    void terminal_initialize() {
        terminal_color = vga_entry_color(vga_color::VGA_COLOR_LIGHT_GREY, vga_color::VGA_COLOR_BLACK);
        terminal_buffer = (uint16_t*) 0xB8000; // VGA text mode buffer
        for(size_t y{}; y < VGA_HEIGHT; ++y) {
            for(size_t x{}; x < VGA_WIDTH; ++x) {
                const size_t index = y * VGA_WIDTH + x;
                terminal_buffer[index] = vga_entry(' ', terminal_color);
            }
        }
    }

    void terminal_setcolor(uint8_t color) {
        terminal_color = color;
    }

    void terminal_setcolor(vga_color fg, vga_color bg) {
        terminal_color = vga_entry_color(fg, bg);
    }

    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, color);
    }

    void scroll_down() {
        //terminal_column = 0; <- should be redundant
        //clear line 1
        for(size_t i{0}; i < VGA_WIDTH; ++i) {
            terminal_buffer[i] = '\0';
        }
        //move everything down
        for(size_t i{VGA_WIDTH}; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
            terminal_buffer[i - VGA_WIDTH] = terminal_buffer[i];
            terminal_buffer[i] = '\0';
        }
    }

    void terminal_putchar(char c) {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if(++terminal_column == VGA_WIDTH) { //reset column(x) if it overflows
            terminal_column = 0;
            if(++terminal_row == VGA_HEIGHT) { //same here
                scroll_down();
                --terminal_row;
            }
        }
    }

    void terminal_write(const char* data, size_t size) {
        for(size_t i{}; i < size; ++i) {
            char c = data[i];
            if(c == '\n') {
                terminal_column = 0;
                if(++terminal_row == VGA_HEIGHT) {
                    scroll_down();
                    --terminal_row;
                }
            }
            else terminal_putchar(c);
        }
    }

    void terminal_writestring(const char* data) {
        terminal_write(data, utility::strlen(data));
    }

}
extern "C" void kernel_main() {
    //init terminal interface
    kernel::terminal_initialize();

    kernel::terminal_writestring("Hello, kernel World!\n");
    kernel::terminal_setcolor(kernel::vga_color::VGA_COLOR_BLUE, kernel::vga_color::VGA_COLOR_GREEN);
    kernel::terminal_writestring("SPOOKY!");
}
