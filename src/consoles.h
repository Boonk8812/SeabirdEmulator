#ifndef CONSOLES_H
#define CONSOLES_H

#include <stdio.h>

#define MAX_CONSOLE_BUFFER 1024
#define COMMAND_DELIMITER ','

typedef enum { CONSOLE_CPU, CONSOLE_ASM, CONSOLE_NUM } ConsoleType;

typedef struct Console CommandConsole;
struct Console {
    ConsoleType type;
    char buffer[MAX_CONSOLE_BUFFER];
    size_t pos;

    void (*write)(CommandConsole *, const char *format, ...);
    int (*read)(CommandConsole *);
    void (*clear)(CommandConsole *);
};

extern Console console[];
extern const Console kConsoleCount;

void console_init();
void console_deinit();

#endif  // CONSOLES_H
