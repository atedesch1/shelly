#include <stdio.h>
#include <stdlib.h>

#ifndef ERROR_HEADER
#define ERROR_HEADER

struct error {
    int type;
    char *message;
};
typedef struct error error;

error *new_error(int type, char *message);

void free_error(error **err);

void print_error(error *err);

#endif // !ERROR_HEADER
