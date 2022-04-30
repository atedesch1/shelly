#include "executer.h"

void execute_command(program_call **program_calls, char **redirect_paths)
{
    bool is_first_program_call = true;
    for (program_call **p = program_calls; *p != NULL; p++)
    {
        if (fork() == 0)
        { // child process
            if (is_first_program_call && redirect_paths[0] != NULL)
            {
                redirect_input(redirect_paths[0]);
                is_first_program_call = false;
            }
            if (p[1] == NULL && redirect_paths[1] != NULL) // if last program_call and redirect output is not NULL
            {
                redirect_output(redirect_paths[1]);
            }
            if (redirect_paths[2] != NULL)
            {
                redirect_erroutput(redirect_paths[2]);
            }
            if (execve((*p)->program, (*p)->params, (*p)->envparams) == -1) // execute program
            {
                perror("couldn't execute program");
            }
        }
        else
        {
            wait(NULL);
        }
    }
}

void redirect_input(char *input_path)
{
    int fd = open(input_path, O_RDONLY);
    if (fd == -1)
    {
        perror("couldn't open");
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
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

void redirect_erroutput(char *erroutput_path)
{
    int fd = open(erroutput_path, O_WRONLY | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("couldn't open");
    }
    dup2(fd, STDERR_FILENO);
    close(fd);
}