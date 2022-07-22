#include "parser.h"

error *parse_input(const char *input, job **job)
{
    char **tokens = NULL;
    tokenize_input(input, &tokens);

    error *err = validate_input((const char **)tokens);

    if (err != NULL)
    {
        return err;
    }

    create_job(&(*job));

    parse_programs((const char **)tokens, &(*job));

    parse_redirects((const char **)tokens, &(*job));

    for (char **p = tokens; *p != NULL; p++)
    {
        free(*p);
    }
    free(tokens);

    return err;
}

void tokenize_input(const char *input, char ***tokens)
{
    char *input_copy = strdup(input);

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

error *validate_input(const char **tokens)
{
    bool encountered_redirects = false;
    bool found_input_redirect = false;
    bool found_output_redirect = false;
    bool found_erroutput_redirect = false;

    if (is_pipe_token(tokens[0]))
    {
        return new_error(100, "expected program found pipe");
    }

    if (is_redirect_token(tokens[0]))
    {
        return new_error(100, "expected program found redirect");
    }

    for (const char **token = tokens, *last_token = ""; *token != NULL; token++)
    {
        if (is_pipe_token(*token))
        {
            if (encountered_redirects)
            {
                return new_error(104, "found pipe after redirect");
            }

            token++;

            if (*token == NULL)
            {
                return new_error(101, "expected program found null");
            }

            if (is_pipe_token(*token))
            {
                return new_error(100, "expected program found pipe");
            }

            if (is_redirect_token(*token))
            {
                return new_error(100, "expected program found redirect");
            }
        }
        else if (is_redirect_token(*token))
        {
            if (is_redirect_input_token(*token))
            {
                if (found_input_redirect)
                {
                    return new_error(105, "found more than one input redirect");
                }

                found_input_redirect = true;
            }
            else if (is_redirect_output_token(*token))
            {
                if (found_output_redirect)
                {
                    return new_error(105, "found more than one output redirect");
                }

                found_output_redirect = true;
            }
            else if (is_redirect_erroutput_token(*token))
            {
                if (found_erroutput_redirect)
                {
                    return new_error(105, "found more than one error output redirect");
                }

                found_erroutput_redirect = true;
            }

            token++;

            if (*token == NULL)
            {
                return new_error(103, "expected path found null");
            }

            if (is_pipe_token(*token))
            {
                return new_error(102, "expected path found pipe");
            }

            if (is_redirect_token(*token))
            {
                return new_error(102, "expected path found redirect");
            }

            encountered_redirects = true;
        }
        else if (encountered_redirects && !is_redirect_token(last_token))
        {
            return new_error(106, "expected redirect found path");
        }

        last_token = *token;
    }

    return NULL;
}

void parse_programs(const char **tokens, job **job)
{
    process *current_process = (*job)->head_process;
    int num_args = 0;

    for (const char **token = tokens; *token != NULL; token++)
    {
        if (is_pipe_token(*token))
        {
            create_process(&(current_process->next));
            current_process = current_process->next;

            num_args = 0;
            continue;
        }

        if (is_redirect_token(*token))
        {
            break;
        }

        if (num_args == 0)
        {
            current_process->program = strdup(*token);

            num_args++;
            current_process->argv = (char **)malloc(sizeof(char *));
            current_process->argv[0] = strdup(*token);

            // envp not supported
            current_process->envp = (char **)malloc(2 * sizeof(char *));
            current_process->envp[0] = strdup("");
            current_process->envp[1] = NULL;
        }
        else
        {
            num_args++;
            current_process->argv = (char **)realloc(current_process->argv, num_args * sizeof(char *));
            current_process->argv[num_args - 1] = strdup(*token);
        }
    }
}

void parse_redirects(const char **tokens, job **job)
{
    for (const char **token = tokens, *last_token = ""; *token != NULL; token++)
    {
        if (is_redirect_input_token(last_token))
        {
            (*job)->io->input = strdup(*token);
        }
        else if (is_redirect_output_token(last_token))
        {
            (*job)->io->output = strdup(*token);
        }
        else if (is_redirect_erroutput_token(last_token))
        {
            (*job)->io->err_output = strdup(*token);
        }

        last_token = *token;
    }
}