#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "program_parser.h"

#ifndef EXECUTER
#define EXECUTER

// executes command
void execute_command(program_call **program_calls, char **fds);

#endif // !EXECUTER