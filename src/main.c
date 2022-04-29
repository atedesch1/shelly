#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "program_parser.h"

int main(int argc, char **argv)
{
    int prompt_count = 0;

    char *input = NULL;
    program_call **program_calls = NULL;
    char **fds = NULL;

    while (1)
    {
        display_prompt(&prompt_count);
        read_input(&input);
        if (!is_valid_input(input))
            continue;
        parse_command(input, &program_calls, &fds);
        free(input);
        free(program_calls);
        free(fds);
    }

    return 0;
}