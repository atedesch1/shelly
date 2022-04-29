#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 200

// displays ~> prompt
void display_prompt(int *prompt_count);

// reads input by modifying input string
void read_input(char **input);

// returns if input is valid
bool is_valid_input(const char *input);