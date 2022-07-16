#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "program_call.h"
#include "redirects.h"

#ifndef EXECUTOR
#define EXECUTOR

#define RWX_PERMISSION_ALL 0777

// executes command
void execute_command(program_call **program_calls, redirects *redirects);

// makes fd_input point to input file descriptor
void set_input(int def_input, int *fd_input, char *redirect_input_path);

// makes fd_output point to output file descriptor
void set_output(int def_output, int *fd_output, char *redirect_output_path);

// makes fd_erroutput point to error output file descriptor
void set_erroutput(int def_erroutput, int *fd_erroutput, char *redirect_erroutput_path);

#endif // !EXECUTOR