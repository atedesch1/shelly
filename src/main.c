#include <stdio.h>

#include "interface.h"

int main(int argc, char **argv)
{
    int prompt_count = 0;

    char *input = NULL;

    while (1)
    {
        display_prompt(&prompt_count);
        read_input(&input);
    }

    return 0;
}