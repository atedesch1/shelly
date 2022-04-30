#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "program_parser.h"
#include "executer.h"

int main()
{
    int prompt_count = 0;

    char *input = NULL;
    program_call **program_calls = NULL;
    char **redirect_paths = NULL;

    while (1)
    {
        display_prompt(&prompt_count);
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

    return 0;
}