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

void read_input(char **input)
{
    size_t line_size = 0;
    getline(&(*input), &line_size, stdin);
}

bool is_exit(const char *input)
{
    char *input_copy = (char *) malloc(sizeof(input));
    strcpy(input_copy, input);

    char *token = strtok(input_copy, " ");
    bool is_exit = strcmp(token, "exit") == 0;

    free(input_copy);
    return is_exit;
}

bool is_clear_screen(const char *input)
{
    char *input_copy = (char *) malloc(sizeof(input));
    strcpy(input_copy, input);

    char *token = strtok(input_copy, " ");
    bool is_clear_screen = strcmp(token, "cls") == 0;
    
    free(input_copy);
    return is_clear_screen;
}