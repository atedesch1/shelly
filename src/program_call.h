#ifndef PROGRAM_CALL_HEADER
#define PROGRAM_CALL_HEADER

struct program_call {
    char *program;
    char **argv;
    char **envp;
};

typedef struct program_call program_call;

#endif // !PROGRAM_CALL_HEADER
