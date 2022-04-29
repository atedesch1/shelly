#include "program_parser.h"
#include "string.h"

void parse_command(const char *input, program_call ***program_calls, char ***fds)
{
    char *command_string = (char *)malloc((strlen(input) + 1) * sizeof(char));
    strcpy(command_string, input);

    *fds = parse_redirects(&command_string);

    int num_program_calls = get_num_program_calls(command_string);
    char **program_strs = break_into_program_strings(command_string, num_program_calls);

    *program_calls = (program_call **)malloc((num_program_calls + 1) * sizeof(program_call *));

    for (int i = 0; i < num_program_calls; i++)
    {
        (*program_calls)[i] = parse_program_call(program_strs[i]);
    }
    (*program_calls)[num_program_calls] = NULL; // end
}

char **parse_redirects(char **command_string)
{
    char **fds = (char **)malloc(NUM_FILE_DESCRIPTORS * sizeof(char *));

    char *command_cpy = (char *)malloc((strlen(*command_string) + 1) * sizeof(char *));
    strcpy(command_cpy, *command_string);

    strtok(*command_string, "<>"); // removes redirects from command_string

    char *token = strtok(command_cpy, WHITESPACE_TOKEN);
    char *last_token = NULL;
    while (token != NULL)
    {
        if (last_token != NULL)
        {
            if (strcmp(last_token, "<") == 0)
            {
                fds[0] = (char *)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(fds[0], token);
            }
            else if (strcmp(last_token, ">") == 0)
            {
                fds[1] = (char *)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(fds[1], token);
            }
            else if (strcmp(last_token, "2>") == 0)
            {
                fds[2] = (char *)malloc((strlen(token) + 1) * sizeof(char));
                strcpy(fds[2], token);
            }
        }
        last_token = token;
        token = strtok(NULL, WHITESPACE_TOKEN);
    }
    return fds;
}

program_call *parse_program_call(const char *program_str)
{
    program_call *parsed_program = (program_call *)malloc(sizeof(program_call));
    int num_program_params = get_num_program_params(program_str);

    char *program_str_cpy = (char *)malloc((strlen(program_str) + 1) * sizeof(char *));
    strcpy(program_str_cpy, program_str);

    // set envparams to { "", NULL }
    parsed_program->envparams = (char **)malloc(2 * sizeof(char *));
    parsed_program->envparams[0] = "";
    parsed_program->envparams[1] = NULL;

    char *token = strtok(program_str_cpy, WHITESPACE_TOKEN);
    if (token != NULL)
        parsed_program->program = token;

    parsed_program->params = (char **)malloc((num_program_params + 1) * sizeof(char *));

    for (int i = 0; i < num_program_params && token != NULL; i++)
    {
        parsed_program->params[i] = token;
        token = strtok(NULL, WHITESPACE_TOKEN);
    }

    parsed_program->params[num_program_params] = NULL; // end

    return parsed_program;
}

char **break_into_program_strings(const char *input, const int num_program_calls)
{
    char **program_strs = (char **)malloc((num_program_calls + 1) * sizeof(char *));

    char *split = (char *)malloc((strlen(input) + 1) * sizeof(char *));
    strcpy(split, input);

    int program_count = 0;
    for (char *token = strtok(split, PIPE_TOKEN); token != NULL; token = strtok(NULL, PIPE_TOKEN))
    {
        program_strs[program_count++] = token;
    }
    program_strs[num_program_calls] = NULL; // end

    return program_strs;
}

int get_num_program_calls(const char *input)
{
    int num_program_calls = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '|')
        {
            num_program_calls++;
        }
    }
    return num_program_calls + 1;
}

int get_num_program_params(const char *program_str)
{
    int num_program_params = 0;

    char *program_str_cpy = (char *)malloc((strlen(program_str) + 1) * sizeof(char *));
    strcpy(program_str_cpy, program_str);

    // counts number of params
    for (char *token = strtok(program_str_cpy, WHITESPACE_TOKEN); token != NULL; token = strtok(NULL, WHITESPACE_TOKEN), num_program_params++);

    return num_program_params;
}