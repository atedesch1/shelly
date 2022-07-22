#include "shell.h"

void init_shell()
{
    init_screen();
}

int run_shell()
{
    char *input = NULL;
    job *job = NULL;

    init_shell();

    while (true)
    {
        display_prompt();

        read_input(&input);

        if (is_empty(input))
        {
            continue;
        }

        if (is_exit(input))
        {
            break;
        }

        if (is_clear_screen(input))
        {
            clear_screen();
            continue;
        }
        
        error *err = parse_input(input, &job);

        if (err != NULL)
        {
            print_error(err);
            free_error(&err);
            continue;
        }

        execute_job(job);

        free(input);
        free_job(&job);
    }

    return EXIT_SUCCESS;
}
