#include "main.h"

/**
 * swapChar - Swaps | and & for non-printed chars.
 *
 * @input: Input string.
 * @bool: Type of swap.
 * Return: Swapped string.
 */
char *swapChar(char *input, int bool)
{
    int i;

    if (bool == 0)
    {
        for (i = 0; input[i]; i++)
        {
            if (input[i] == '|')
            {
                if (input[i + 1] != '|')
                    input[i] = 16;
                else
                    i++;
            }

            if (input[i] == '&')
            {
                if (input[i + 1] != '&')
                    input[i] = 12;
                else
                    i++;
            }
        }
    }
    else
    {
        for (i = 0; input[i]; i++)
        {
            input[i] = (input[i] == 16 ? '|' : input[i]);
            input[i] = (input[i] == 12 ? '&' : input[i]);
        }
    }

    return input;
}

/**
 * addNodes - Adds separators and command lines to the lists.
 *
 * @headS: Head of the separator list.
 * @headL: Head of the command lines list.
 * @input: Input string.
 */
void addNodes(sep_list **headS, line_list **headL, char *input)
{
    int i;
    char *line;

    input = swapChar(input, 0);

    for (i = 0; input[i]; i++)
    {
        if (input[i] == ';')
            add_sep_node_end(headS, input[i]);

        if (input[i] == '|' || input[i] == '&')
        {
            add_sep_node_end(headS, input[i]);
            i++;
        }
    }

    line = _strtok(input, ";|&");
    do
    {
        line = swapChar(line, 1);
        add_line_node_end(headL, line);
        line = _strtok(NULL, ";|&");
    } while (line != NULL);
}

/**
 * goNext - Moves to the next command line stored.
 *
 * @listS: Separator list.
 * @listL: Command line list.
 * @datash: Data structure.
 */
void goNext(sep_list **listS, line_list **listL, data_shell *datash)
{
    int loopSep;
    sep_list *lsS;
    line_list *lsL;

    loopSep = 1;
    lsS = *listS;
    lsL = *listL;

    while (lsS != NULL && loopSep)
    {
        if (datash->status == 0)
        {
            if (lsS->separator == '&' || lsS->separator == ';')
                loopSep = 0;
            if (lsS->separator == '|')
                lsL = lsL->next, lsS = lsS->next;
        }
        else
        {
            if (lsS->separator == '|' || lsS->separator == ';')
                loopSep = 0;
            if (lsS->separator == '&')
                lsL = lsL->next, lsS = lsS->next;
        }

        if (lsS != NULL && !loopSep)
            lsS = lsS->next;
    }

    *listS = lsS;
    *listL = lsL;
}

/**
 * splitCommands - Splits command lines according to separators ;, | and & and executes them.
 *
 * @datash: Data structure.
 * @input: Input string.
 * Return: 0 to exit, 1 to continue.
 */
int splitCommands(data_shell *datash, char *input)
{
    sep_list *headS, *listS;
    line_list *headL, *listL;
    int loop;

    headS = NULL;
    headL = NULL;

    addNodes(&headS, &headL, input);

    listS = headS;
    listL = headL;

    while (listL != NULL)
    {
        datash->input = listL->line;
        datash->args = split_line(datash->input);
        loop = exec_line(datash);
        free(datash->args);

        if (loop == 0)
            break;

        goNext(&listS, &listL, datash);

        if (listL != NULL)
            listL = listL->next;
    }

    free_sep_list(&headS);
    free_line_list(&headL);

    if (loop == 0)
        return 0;
    return 1;
}

/**
 * splitLine - Tokenizes the input string.
 *
 * @input: Input string.
 * Return: String splitted.
 */
char **splitLine(char *input)
{
    size_t bsize;
    size_t i;
    char **tokens;
    char *token;

    bsize = TOK_BUFSIZE;
    tokens = malloc(sizeof(char *) * (bsize));

    if (tokens == NULL)
    {
        write(STDERR_FILENO, ": allocation error\n", 18);
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, TOK_DELIM);
    tokens[0] = token;

    for (i = 1; token != NULL; i++)
    {
        if (i == bsize)
        {
            bsize += TOK_BUFSIZE;
            tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);

            if (tokens == NULL)
            {
                write(STDERR_FILENO, ": allocation error\n", 18);
                exit(EXIT_FAILURE);
            }
        }

        token = _strtok(NULL, TOK_DELIM);
        tokens[i] = token;
    }

    return tokens;
}
