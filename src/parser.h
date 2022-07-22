#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "job.h"

#ifndef PARSER_HEADER
#define PARSER_HEADER

#define WHITESPACE_TOKEN " \n\r"
#define PIPE_TOKEN "|"
#define INPUT_REDIRECT_TOKEN "<"
#define OUTPUT_REDIRECT_TOKEN ">"
#define ERR_OUTPUT_REDIRECT_TOKEN "2>"

error *parse_input(const char *input, job **job);

void tokenize_input(const char *input, char ***tokens);

error *validate_input(const char **tokens);

void parse_programs(const char **tokens, job **job);

void parse_redirects(const char **tokens, job **job);

bool is_redirect_token(const char *token);

bool is_redirect_input_token(const char *token);

bool is_redirect_output_token(const char *token);

bool is_redirect_erroutput_token(const char *token);

bool is_pipe_token(const char *token);

#endif // !PARSER_HEADER
