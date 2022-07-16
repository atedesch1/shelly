#ifndef REDIRECTS_HEADER
#define REDIRECTS_HEADER

struct redirects {
    char *input;
    char *output;
    char *err_output;
};
typedef struct redirects redirects;

#endif // !REDIRECTS_HEADER