#include "shell.h"

void init_shell()
{
    init_screen();
}

int run_shell()
{
    char *input = NULL;
    program_call **program_calls = NULL;
    redirects *redirects = NULL;

    init_shell();

    while (true)
    {
        display_prompt();

        read_input(&input);

        if (is_exit(input))
        {
            break;
        }

        if (is_clear_screen(input))
        {
            clear_screen();
            continue;
        }

        int err = parse_input(input, &program_calls, &redirects);

        if (err != 0)
        {
            printf("err: %d\n", err);
            continue;
        }

        execute_command(program_calls, redirects);

        free(input);
        // free program_calls
        // free redirects
    }

    return EXIT_SUCCESS;
}
