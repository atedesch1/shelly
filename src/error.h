#ifndef ERROR_HEADER
#define ERROR_HEADER

struct error {
    int type;
    char *message;
};

typedef struct error error;

#endif // !ERROR_HEADER
