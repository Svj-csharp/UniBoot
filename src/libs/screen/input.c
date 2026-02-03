#include "input.h"
#include "output.h"


static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


static const char scancode_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char getchar(void) {
    uint8_t scancode = 0;
    
    
    while (!(inb(0x64) & 1));
    
    scancode = inb(0x60);

    
    if (scancode & 0x80) return 0;
    
    char c = scancode_map[scancode];
    
    
    if (c > 0) terminal_putchar(c);
    
    return c;
}

void gets(char* buffer, size_t max_size) {
    size_t i = 0;
    while (i < max_size - 1) {
        char c = getchar();
        
        if (c == 0) continue;         
        if (c == '\n') break;         
        
        if (c == '\b') {              
            if (i > 0) i--;
            continue;
        }
        
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}
