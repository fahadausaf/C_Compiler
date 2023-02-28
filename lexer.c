#include "compiler.h"
#include "helpers/vector.h"
#include "helpers/buffer.h"

#define LEX_GETC_IF(buffer, c, exp)     \
    for (c = peekc(); exp; c = peekc()) \
    {                                   \
        buffer_write(buffer, c);        \
        nextc();                        \
    }                                   \

static struct lex_process *lex_process;

static char peekc()
{
    return lex_process->function->peek_char(lex_process);
}

static void pushc(char c)
{
    lex_process->function->push_char(lex_process, c);
}

const char* read_number_str()
{
    const char* num = NULL
    struct buffer* buffer = buffer_create();
    char c = peekc()
}

struct token* token_make_number_for_value(unsigned long number)
{

}

struct token *token_make_number()
{
    return token_make_number_for_value(read_number());
}

struct token *read_next_token()
{
    struct token *token = NULL;
    char c = peekc();

    switch (c)
    {
    NUMERIC_CASE:
        token = token_make_number();
        break;

    case EOF:
        // we have finished lexical analysis on the file
        break;
    default:
        compiler_error(lex_process->compiler, "Unexpected token\n");
    }

    return token;
}

int lex(struct lex_process *process)
{
    process->current_expression_count = 0;
    process->parenthesis_buffer = NULL;
    lex_process = process;
    process->pos.filename = process->compiler->cfile.abs_path;

    struct token *token = read_next_token();
    while (token)
    {
        vector_push(process->token_vec, token);
        token = read_next_token();
    }

    return LEXICAL_ANALYSIS_ALL_OK;
}