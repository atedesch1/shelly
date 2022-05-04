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

// initializes screen
void init_screen();

// clears screen
void clear_screen();

// paints string with color given by ansi_color
char *paint_str(char *str, char *ansi_color, char *ansi_reset);

// displays ~> prompt
void display_prompt();

// reads input and returns it
char *read_input();

// returns if input is valid
bool is_valid_input(const char *input);

// checks if input was "exit"
bool is_exit(const char *input);

#endif // !INTERFACE
