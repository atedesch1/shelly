#include "interface.h"
#include "program_parser.h"
#include "executor.h"

int main()
{
    char *input = NULL;
    program_call **program_calls = NULL;
    char **redirect_paths = NULL;

    init_screen();

    while (true)
    {
        display_prompt();
        input = read_input();
        if (!is_valid_input(input))
            continue;
        if (is_exit(input))
            break;

        parse_command(input, &program_calls, &redirect_paths);
        execute_command(program_calls, redirect_paths);

        free(input);
        free(program_calls);
        free(redirect_paths);
    }

    return EXIT_SUCCESS;
}