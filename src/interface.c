#include "interface.h"

void init_screen()
{
    clear_screen();
    printf(WELCOME_MESSAGE);
}

void clear_screen()
{
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

char *paint_str(char *str, char *ansi_color, char *ansi_reset)
{
    int painted_str_len = 1 + strlen(str) + strlen(ansi_color) + strlen(ansi_reset);
    char *painted_str = malloc(painted_str_len * sizeof(char));
    strcpy(painted_str, ansi_color);
    strcat(painted_str, str);
    strcat(painted_str, ansi_reset);
    return painted_str;
}

void display_prompt()
{
    char *prompt = paint_str("~>", MAG, reset);
    printf("%s ", prompt);
    free(prompt);
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