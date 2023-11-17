#include "main.h"

/**
 * withoutComment - Deletes comments from the input.
 *
 * @in: Input string.
 * Return: Input without comments.
 */
char *withoutComment(char *in)
{
    int i, upTo;

    upTo = 0;
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '#')
        {
            if (i == 0)
            {
                free(in);
                return NULL;
            }

            if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
                upTo = i;
        }
    }

    if (upTo != 0)
    {
        in = _realloc(in, i, upTo + 1);
        in[upTo] = '\0';
    }

    return in;
}

/**
 * shellLoop - Shell loop.
 *
 * @datash: Data relevant (av, input, args).
 */
void shellLoop(data_shell *datash)
{
    int loop, iEof;
    char *input;

    loop = 1;
    while (loop == 1)
    {
        write(STDIN_FILENO, "^-^ ", 4);
        input = read_line(&iEof);
        if (iEof != -1)
        {
            input = withoutComment(input);
            if (input == NULL)
                continue;

            if (checkSyntaxError(datash, input) == 1)
            {
                datash->status = 2;
                free(input);
                continue;
            }

            input = repVar(input, datash);
            loop = splitCommands(datash, input);
            datash->counter += 1;
            free(input);
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}
