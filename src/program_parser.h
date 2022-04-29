#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROGRAM_PARSER
#define PROGRAM_PARSER

#define NUM_FILE_DESCRIPTORS 3
#define WHITESPACE_TOKEN " \n\r"
#define PIPE_TOKEN "|"

struct program_call
{
    char *program;
    char **params;
    char **envparams;
};
typedef struct program_call program_call;

// parses input string into programs and redirects
void parse_command(const char *input, program_call ***program_calls, char ***fds);

// parses redirects
// removes string containing redirects from command_string
// returns an array with 3 strings representing file descriptors [stdin, stdout, stderrout]
// if a redirect is not provided returns NULL on position
char **parse_redirects(char **command_string);

// parses a program call string into a program_call
program_call *parse_program_call(const char *program_str);

// breaks input into program call strings
char **break_into_program_strings(const char *input, const int num_program_calls);

// returns number of program calls inside a string
int get_num_program_calls(const char *input);

// returns number of program parameters inside a program call string
int get_num_program_params(const char *program_str);

#endif // !PROGRAM_PARSER