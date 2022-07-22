#include "error.h"

error *new_error(int type, char *message)
{
    error *err = (error *)malloc(sizeof(error));
    err->type = type;
    err->message = message;
    return err;
}

void free_error(error **err)
{
    free(*err);
}

void print_error(error *err)
{
    printf("shelly (%d): %s\n", err->type, err->message);
}