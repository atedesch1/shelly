#include <stdlib.h>

#ifndef JOB_HEADER
#define JOB_HEADER

struct process {
    char *program;
    char **argv;
    char **envp;
    struct process *next;
};
typedef struct process process;

void create_process(process **p);
void free_process(process **p);

struct io {
    char *input;
    char *output;
    char *err_output;
};
typedef struct io io;

void create_io(io **i);
void free_io(io **i);

struct job {
    process *head_process;   
    io *io;
};
typedef struct job job;

void create_job(job **j);
void free_job(job **j);

#endif // !JOB_HEADER
