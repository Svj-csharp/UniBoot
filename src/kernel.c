#include "libs/screen/output.h"
#include "libs/screen/input.h"

void kmain(void) {
    terminal_initialize();
    terminal_setcolor(make_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("UniBoot kernel is booted\n");
    terminal_writestring("Use keyboard to interact...\n\n");

    char buffer[64];

    
    while (1) {
        terminal_setcolor(make_color(COLOR_WHITE, COLOR_BLACK));
        terminal_writestring("> "); 
        
        gets(buffer, 64);
        
        terminal_newline();
        terminal_setcolor(make_color(COLOR_LIGHT_BLUE, COLOR_BLACK));
        terminal_writestring("Kernel received: ");
        terminal_writestring(buffer);
        terminal_newline();
    }
}