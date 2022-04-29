#include "executer.h"

void execute_command(program_call **program_calls, char **fds)
{
    for (program_call **p = program_calls; *p != NULL; p++)
    {
        if (fork() == 0)
        {   // child process
            execve((*p)->program, (*p)->params, (*p)->envparams);
        }
        else
        {
            wait(NULL);
        }
    }
}