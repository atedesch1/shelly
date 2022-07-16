#include "interface.h"
#include "parser.h"
#include "executor.h"

#include "program_call.h"
#include "redirects.h"

#ifndef SHELL_HEADER
#define SHELL_HEADER

// Initializes shell
void init_shell();

// Runs shell loop
int run_shell();

#endif // !SHELL_HEADER
