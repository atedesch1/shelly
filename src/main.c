#include <stdio.h>

#include "interface.h"

int main(int argc, char **argv)
{
    int prompt_count = 0;
    while (1)
    {
        display_prompt(&prompt_count);
        char *input = read_input();
    }
    return 0;
}