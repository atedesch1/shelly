#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "program_call.h"
#include "redirects.h"

#ifndef PARSER_HEADER
#define PARSER_HEADER

#define END_STR_CHAR '\0'
#define SPACE_CHAR ' '
#define WHITESPACE_TOKEN " \n\r"
#define PIPE_TOKEN "|"
#define INPUT_REDIRECT_TOKEN "<"
#define OUTPUT_REDIRECT_TOKEN ">"
#define ERR_OUTPUT_REDIRECT_TOKEN "2>"

int parse_input(const char *input, program_call ***program_calls, redirects **redirects);

void tokenize_input(const char *input, char ***tokens);

int validate_input(const char **tokens);

void parse_programs(const char **tokens, program_call ***program_calls);

void parse_redirects(const char **tokens, redirects **redirects);

bool is_redirect_token(const char *token);

bool is_redirect_input_token(const char *token);

bool is_redirect_output_token(const char *token);

bool is_redirect_erroutput_token(const char *token);

bool is_pipe_token(const char *token);

#endif // !PARSER_HEADER
