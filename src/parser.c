#include "parser.h"

int parse_input(const char *input, program_call ***program_calls, redirects **redirects)
{
    char **tokens = NULL;
    tokenize_input(input, &tokens);

    int err = validate_input((const char **)tokens);

    if (err != 0)
    {
        return err;
    }

    parse_programs((const char **)tokens, &(*program_calls));

    parse_redirects((const char **)tokens, &(*redirects));

    for (char **p = tokens; *p != NULL; p++)
    {
        free(*p);
    }
    free(tokens);

    return 0;
}

void tokenize_input(const char *input, char ***tokens)
{
    char *input_copy = (char *)malloc(sizeof(input));
    strcpy(input_copy, input);

    int num_tokens = 0;

    char *token = strtok(input_copy, WHITESPACE_TOKEN);

    while (token != NULL)
    {
        num_tokens++;
        *tokens = (char **)realloc(*tokens, num_tokens * sizeof(char *));
        (*tokens)[num_tokens - 1] = (char *)malloc(sizeof(token));
        strcpy((*tokens)[num_tokens - 1], token);
        token = strtok(NULL, WHITESPACE_TOKEN);
    }

    *tokens = (char **)realloc(*tokens, (num_tokens + 1) * sizeof(char *));
    (*tokens)[num_tokens] = NULL;

    free(input_copy);
}

bool is_redirect_token(const char *token)
{
    return strcmp(token, INPUT_REDIRECT_TOKEN) == 0 ||
           strcmp(token, OUTPUT_REDIRECT_TOKEN) == 0 ||
           strcmp(token, ERR_OUTPUT_REDIRECT_TOKEN) == 0;
}

bool is_redirect_input_token(const char *token)
{
    return strcmp(token, INPUT_REDIRECT_TOKEN) == 0;
}

bool is_redirect_output_token(const char *token)
{
    return strcmp(token, OUTPUT_REDIRECT_TOKEN) == 0;
}

bool is_redirect_erroutput_token(const char *token)
{
    return strcmp(token, ERR_OUTPUT_REDIRECT_TOKEN) == 0;
}

bool is_pipe_token(const char *token)
{
    return strcmp(token, PIPE_TOKEN) == 0;
}

int validate_input(const char **tokens)
{
    bool encountered_redirects = false;
    bool found_input_redirect = false;
    bool found_output_redirect = false;
    bool found_erroutput_redirect = false;

    for (const char **token = tokens, *last_token = ""; *token != NULL; token++)
    {
        if (is_pipe_token(*token))
        {
            if (encountered_redirects)
            {
                return 1; // redirects should be at the end
            }

            token++;

            if (*token == NULL)
            {
                return 3; // expected program found null
            }

            if (is_pipe_token(*token) || is_redirect_token(*token))
            {
                return 4; // expected program found pipe / redirect
            }
        }
        else if (is_redirect_token(*token))
        {
            if (is_redirect_input_token(*token))
            {
                if (found_input_redirect)
                {
                    return 2; // found 2 input redirects
                }

                found_input_redirect = true;
            }
            else if (is_redirect_output_token(*token))
            {
                if (found_output_redirect)
                {
                    return 2; // found 2 output redirects
                }

                found_output_redirect = true;
            }
            else if (is_redirect_erroutput_token(*token))
            {
                if (found_erroutput_redirect)
                {
                    return 2; // found 2 erroutput redirects
                }

                found_erroutput_redirect = true;
            }

            token++;

            if (*token == NULL)
            {
                return 3; // expected redirect found null
            }

            if (is_pipe_token(*token) || is_redirect_token(*token))
            {
                return 4; // expected path found pipe / redirect
            }

            encountered_redirects = true;
        }
        else if (encountered_redirects && !is_redirect_token(last_token))
        {
            return 5; // expected single path for redirect
        }

        last_token = *token;
    }

    return 0;
}

void parse_programs(const char **tokens, program_call ***program_calls)
{
    int num_programs = 0;
    int num_program_args = 0;

    bool is_new_program = true;

    for (const char **token = tokens; *token != NULL; token++)
    {
        if (is_pipe_token(*token))
        {
            program_call *p = (*program_calls)[num_programs - 1];

            p->argv = (char **)realloc(p->argv, (num_program_args + 1) * sizeof(char *));
            p->argv[num_program_args] = NULL;

            is_new_program = true;
            num_program_args = 0;
            continue;
        }

        if (is_redirect_token(*token))
        {
            program_call *p = (*program_calls)[num_programs - 1];

            p->argv = (char **)realloc(p->argv, (num_program_args + 1) * sizeof(char *));
            p->argv[num_program_args] = NULL;

            break;
        }

        if (is_new_program)
        {
            program_call *p = (program_call *)malloc(sizeof(program_call));

            p->program = (char *)malloc(sizeof(*token));
            strcpy(p->program, *token);

            p->argv = (char **)malloc(sizeof(char *));
            p->argv[0] = (char *)malloc(sizeof(*token));
            strcpy(p->argv[0], *token);

            // envp not supported
            p->envp = (char **)malloc(2 * sizeof(char *));
            p->envp[0] = "";
            p->envp[1] = NULL;

            num_programs++;
            num_program_args++;

            *program_calls = (program_call **)realloc(*program_calls, num_programs * sizeof(program_call *));
            (*program_calls)[num_programs - 1] = p;

            is_new_program = false;
        }
        else
        {
            program_call *p = (*program_calls)[num_programs - 1];

            num_program_args++;

            p->argv = (char **)realloc(p->argv, num_program_args * sizeof(char *));
            p->argv[num_program_args - 1] = (char *)malloc(sizeof(*token));
            strcpy(p->argv[num_program_args - 1], *token);
        }
    }

    *program_calls = (program_call **)realloc(*program_calls, (num_programs + 1) * sizeof(program_call *));
    (*program_calls)[num_programs] = NULL;
}

void parse_redirects(const char **tokens, redirects **redirects)
{
    *redirects = malloc(sizeof(redirects));

    (*redirects)->input = NULL;
    (*redirects)->output = NULL;
    (*redirects)->err_output = NULL;

    for (const char **token = tokens, *last_token = ""; *token != NULL; token++)
    {
        if (is_redirect_input_token(last_token))
        {
            (*redirects)->input = (char *)malloc(sizeof(*token));
            strcpy((*redirects)->input, *token);
        }
        else if (is_redirect_output_token(last_token))
        {
            (*redirects)->output = (char *)malloc(sizeof(*token));
            strcpy((*redirects)->output, *token);
        }
        else if (is_redirect_erroutput_token(last_token))
        {
            (*redirects)->err_output = (char *)malloc(sizeof(*token));
            strcpy((*redirects)->err_output, *token);
        }

        last_token = *token;
    }
}