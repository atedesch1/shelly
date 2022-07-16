#include "executor.h"

void execute_command(program_call **program_calls, redirects *redirects)
{
    pid_t child_pid;

    // saves default input/output
    int def_input = dup(STDIN_FILENO);
    int def_output = dup(STDOUT_FILENO);
    int def_erroutput = dup(STDERR_FILENO);

    int fd_input;
    int fd_output;
    int fd_erroutput;

    // sets error output for any process
    set_erroutput(def_erroutput, &fd_erroutput, redirects->err_output);
    // redirect error output
    dup2(fd_erroutput, STDERR_FILENO);
    close(fd_erroutput);

    // sets input for first process
    set_input(def_input, &fd_input, redirects->input);

    for (program_call **p = program_calls; *p != NULL; p++)
    {
        // redirect input
        dup2(fd_input, STDIN_FILENO);
        close(fd_input);

        if (p[1] == NULL)
        { // last process
            // sets output for last process
            set_output(def_output, &fd_output, redirects->err_output);
        }
        else
        {
            int fdpipe[2];
            if (pipe(fdpipe) == -1)
            {
                perror("couldn't create pipe");
                exit(1);
            }
            fd_input = fdpipe[0]; // pipe output from current process to next
            fd_output = fdpipe[1];
        }

        // redirect output
        dup2(fd_output, STDOUT_FILENO);
        close(fd_output);

        child_pid = fork();
        if (child_pid < 0)
        {
            perror("couldn't fork process");
            exit(2);
        }

        if (child_pid == 0)
        { // child process
            if (execve((*p)->program, (*p)->argv, (*p)->envp) == -1)
            {
                perror("couldn't execute program");
                exit(3);
            }
        }
    }

    // restore input/output defaults
    dup2(def_input, STDIN_FILENO);
    close(def_input);
    dup2(def_output, STDOUT_FILENO);
    close(def_output);
    dup2(def_erroutput, STDERR_FILENO);
    close(def_erroutput);

    // waits for last process
    waitpid(child_pid, NULL, 0);
}

void set_input(int def_input, int *fd_input, char *redirect_input_path)
{
    if (redirect_input_path != NULL)
    {
        *fd_input = open(redirect_input_path, O_RDONLY);
    }
    else
    {
        *fd_input = dup(def_input);
    }
}

void set_output(int def_output, int *fd_output, char *redirect_output_path)
{
    if (redirect_output_path != NULL)
    {
        *fd_output = open(redirect_output_path, O_WRONLY | O_CREAT, RWX_PERMISSION_ALL);
    }
    else
    {
        *fd_output = dup(def_output);
    }
}

void set_erroutput(int def_erroutput, int *fd_erroutput, char *redirect_erroutput_path)
{
    if (redirect_erroutput_path != NULL)
    {
        *fd_erroutput = open(redirect_erroutput_path, O_APPEND | O_WRONLY | O_CREAT, RWX_PERMISSION_ALL);
    }
    else
    {
        *fd_erroutput = dup(def_erroutput);
    }
}