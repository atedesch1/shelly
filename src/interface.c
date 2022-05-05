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
    int painted_str_size = sizeof(str) + sizeof(ansi_color) + sizeof(ansi_reset) - 2 * sizeof(char);
    char *painted_str = malloc(painted_str_size);
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
    bool is_valid_input = true;
    char *input_str = (char *)malloc(sizeof(input));
    strcpy(input_str, input);
    char *token = strtok(input_str, WHITESPACE_TOKEN);
    is_valid_input = token != NULL;
    free(input_str);
    return is_valid_input;
}

bool is_exit(const char *input)
{
    bool is_exit = false;
    char *input_str = (char *)malloc(sizeof(input));
    strcpy(input_str, input);
    char *token = strtok(input_str, WHITESPACE_TOKEN);
    is_exit = strcmp(token, "exit") == 0;
    free(input_str);
    return is_exit;
}

bool is_clear_screen(const char *input)
{
    bool is_clear_screen = false;
    char *input_str = (char *)malloc(sizeof(input));
    strcpy(input_str, input);
    char *token = strtok(input_str, WHITESPACE_TOKEN);
    is_clear_screen = strcmp(token, "cls") == 0;
    free(input_str);
    return is_clear_screen;
}