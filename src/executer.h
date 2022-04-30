#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "program_parser.h"

#ifndef EXECUTER
#define EXECUTER

// executes command
void execute_command(program_call **program_calls, char **redirect_paths);

// redirects current process stdin to input_path file
void redirect_input(char *input_path);

// redirects current process stdout to output_path file
void redirect_output(char *output_path);

// redirects current process stderrout to erroutput_path file
void redirect_erroutput(char *erroutput_path);

#endif // !EXECUTER