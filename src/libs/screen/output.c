#include "output.h"
#include <stdbool.h>


#define VGA_MEMORY 0xB8000


#define VGA_WIDTH 80
#define VGA_HEIGHT 25


static terminal_t terminal;


uint8_t make_color(vga_color fg, vga_color bg) {
    return fg | bg << 4;
}


uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}


static void terminal_scroll(void) {
    for (size_t y = 0; y < terminal.height - 1; y++) {
        for (size_t x = 0; x < terminal.width; x++) {
            size_t index_old = y * terminal.width + x;
            size_t index_new = (y + 1) * terminal.width + x;
            terminal.video_memory[index_new] = terminal.video_memory[index_old];
        }
    }
    
    
    size_t last_line = (terminal.height - 1) * terminal.width;
    for (size_t x = 0; x < terminal.width; x++) {
        terminal.video_memory[last_line + x] = make_vgaentry(' ', terminal.color);
    }
}


void terminal_initialize(void) {
    terminal.video_memory = (uint16_t*)VGA_MEMORY;
    terminal.width = VGA_WIDTH;
    terminal.height = VGA_HEIGHT;
    terminal.cursor_x = 0;
    terminal.cursor_y = 0;
    terminal.color = make_color(COLOR_LIGHT_GRAY, COLOR_BLACK);
    
    terminal_clear();
}


void terminal_clear(void) {
    for (size_t y = 0; y < terminal.height; y++) {
        for (size_t x = 0; x < terminal.width; x++) {
            const size_t index = y * terminal.width + x;
            terminal.video_memory[index] = make_vgaentry(' ', terminal.color);
        }
    }
    terminal.cursor_x = 0;
    terminal.cursor_y = 0;
}


void terminal_setcolor(uint8_t color) {
    terminal.color = color;
}


void terminal_putchar(char c) {
    
    if (c == '\n') {
        terminal_newline();
        return;
    }
    
    if (c == '\b') {
        terminal_backspace();
        return;
    }
    
    if (c == '\t') {
        
        for (int i = 0; i < 4; i++) {
            terminal_putchar(' ');
        }
        return;
    }
    
    
    const size_t index = terminal.cursor_y * terminal.width + terminal.cursor_x;
    terminal.video_memory[index] = make_vgaentry(c, terminal.color);
    
    
    if (++terminal.cursor_x == terminal.width) {
        terminal_newline();
    }
}


void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}


void terminal_writestring(const char* data) {
    while (*data != '\0') {
        terminal_putchar(*data);
        data++;
    }
}


void terminal_newline(void) {
    terminal.cursor_x = 0;
    
    if (++terminal.cursor_y == terminal.height) {
        terminal_scroll();
        terminal.cursor_y = terminal.height - 1;
    }
}


void terminal_backspace(void) {
    if (terminal.cursor_x == 0) {
        if (terminal.cursor_y > 0) {
            terminal.cursor_y--;
            terminal.cursor_x = terminal.width - 1;
        } else {
            return; 
        }
    } else {
        terminal.cursor_x--;
    }
    
    const size_t index = terminal.cursor_y * terminal.width + terminal.cursor_x;
    terminal.video_memory[index] = make_vgaentry(' ', terminal.color);
}