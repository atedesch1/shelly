#include "shell.h"
#include "interface.h"
#include "executor.h"
#include "program_parser.h"

int run_shell()
{
    char *input = NULL;
    program_call **program_calls = NULL;
    char **redirect_paths = NULL;

    init_shell();

    while (true)
    {
        display_prompt();
        input = read_input();
        if (!is_valid_input(input))
            continue;
        if (is_exit(input))
            break;
        if (is_clear_screen(input))
        {
            clear_screen();
            continue;
        }

        parse_command(input, &program_calls, &redirect_paths);
        execute_command(program_calls, redirect_paths);

        free(input);
        free(program_calls);
        free(redirect_paths);
    }

    return EXIT_SUCCESS;
}

void init_shell()
{
    init_screen();
}
