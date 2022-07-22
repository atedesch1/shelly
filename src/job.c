#include "job.h"

void create_process(process **p)
{
    *p = (process *)malloc(sizeof(process));
    (*p)->program = NULL;
    (*p)->argv = NULL;
    (*p)->envp = NULL;
    (*p)->next = NULL;
}

void free_process(process **p)
{
    free((*p)->program);

    for (char **ptr = (*p)->argv; *ptr != NULL; ptr++)
    {
        free(*ptr);
    }

    for (char **ptr = (*p)->envp; *ptr != NULL; ptr++)
    {
        free(*ptr);
    }

    free(*p);
}

void create_io(io **i)
{
    *i = (io *)malloc(sizeof(io));
    (*i)->input = NULL;
    (*i)->output = NULL;
    (*i)->err_output = NULL;
}

void free_io(io **i)
{
    free((*i)->input);
    free((*i)->output);
    free((*i)->err_output);
    free(*i);
}

void create_job(job **j)
{
    *j = (job *)malloc(sizeof(job));
    create_process(&((*j)->head_process));
    create_io(&((*j)->io));
}

void free_job(job **j)
{
    process *p = (*j)->head_process;
    while (p != NULL)
    {
        process *next = p->next;
        free_process(&p);
        p = next;
    }

    free_io(&((*j)->io));

    free(*j);
}
