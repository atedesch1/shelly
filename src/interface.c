#include "interface.h"

void init_screen()
{
    clear_screen();
    printf("Hello from \033[0;36mshelly\033[0m\n");
}

void clear_screen()
{
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void display_prompt()
{
    printf("\033[0;35m~> \033[0m");
}

char *read_input()
{
    char *input = NULL;
    size_t line_size = 0;
    getline(&input, &line_size, stdin);
    return input;
}

bool is_valid_input(const char *input) // @TODO validate input
{
    char *input_cpy = (char *)malloc((strlen(input) + 1) * sizeof(char));
    strcpy(input_cpy, input);
    char *token = strtok(input_cpy, WHITESPACE_TOKEN);
    if (token == NULL) return false;
    return true;
}

bool is_exit(const char *input)
{
    char *input_cpy = (char *)malloc((strlen(input) + 1) * sizeof(char));
    strcpy(input_cpy, input);
    char *token = strtok(input_cpy, WHITESPACE_TOKEN);
    return strcmp(token, "exit") == 0;
}