#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "program_parser.h"

#ifndef INTERFACE
#define INTERFACE

// displays ~> prompt
void display_prompt(int *prompt_count);

// reads input and returns it
char *read_input();

// returns if input is valid
bool is_valid_input(const char *input);

// checks if input was "exit"
bool is_exit(const char *input);

#endif // !INTERFACE
