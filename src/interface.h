#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ansi_colors.h"
#include "program_parser.h"

#ifndef INTERFACE
#define INTERFACE

#define CLEAR_SCREEN_ANSI " \e[1;1H\e[2J"
#define WELCOME_MESSAGE "Hello from \e[0;35mshelly\e[0m!\n"

// Initializes screen
void init_screen();

// Clears screen
void clear_screen();

// Paints string with color given by ansi_color
char *paint_str(char *str, char *ansi_color, char *ansi_reset);

// Displays prompt
void display_prompt();

// Reads input from stdin and returns it
char *read_input();

// Returns if input is valid
bool is_valid_input(const char *input);

// Checks if input was "exit"
bool is_exit(const char *input);

#endif // !INTERFACE
