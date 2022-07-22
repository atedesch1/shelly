#include "interface.h"
#include "parser.h"
#include "executor.h"

#include "job.h"
#include "error.h"

#ifndef SHELL_HEADER
#define SHELL_HEADER

// Initializes shell
void init_shell();

// Runs shell loop
int run_shell();

#endif // !SHELL_HEADER
