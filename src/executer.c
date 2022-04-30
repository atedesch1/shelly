#include "executer.h"

void execute_command(program_call **program_calls, char **fds)
{
    for (program_call **p = program_calls; *p != NULL; p++)
    {
        if (fork() == 0)
        { // child process
            if (p[1] == NULL && fds[1] != NULL) // if last program_call and redirect output is not NULL
            {
                redirect_output(fds[1]);
            }
            execve((*p)->program, (*p)->params, (*p)->envparams);
        }
        else
        {
            wait(NULL);
        }
    }
}

void redirect_output(char *output_path)
{
    int fd = open(output_path, O_WRONLY | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("couldn't open");
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}