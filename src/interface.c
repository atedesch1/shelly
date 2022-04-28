#include "interface.h"

void display_prompt(int *prompt_count)
{
    if (*prompt_count == 0)
    { // Clear screen and display welcome
        const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        printf("Hello from shelly :)\n");
    }
    printf("~> "); // prompt
    (*prompt_count)++;
}

char *read_input()
{
    char *input = (char *)malloc(MAX_INPUT_LENGTH * sizeof(char));
    fgets(input, MAX_INPUT_LENGTH, stdin);
    return input;
}