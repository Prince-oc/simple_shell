#include "main.h"

/**
 * checkEnv - Checks if the typed variable is an environment variable.
 *
 * @h: Head of linked list.
 * @in: Input string.
 * @data: Data structure.
 */
void checkEnv(r_var **h, char *in, data_shell *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;
    for (row = 0; _envr[row]; row++)
    {
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    add_rvar_node(h, j, NULL, 0);
}

/**
 * checkVariables - Checks if the typed variable is $$ or $?.
 *
 * @h: Head of the linked list.
 * @in: Input string.
 * @st: Last status of the Shell.
 * @data: Data structure.
 * Return: Number of characters processed.
 */
int checkVariables(r_var **h, char *in, char *st, data_shell *data)
{
    int i, lst, lpd;

    lst = _strlen(st);
    lpd = _strlen(data->pid);

    for (i = 0; in[i]; i++)
    {
        if (in[i] == '$')
        {
            if (in[i + 1] == '?')
                add_rvar_node(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                add_rvar_node(h, 2, data->pid, lpd), i++;
            else if (in[i + 1] == '\n' || in[i + 1] == '\0' || in[i + 1] == ' ' || in[i + 1] == '\t' || in[i + 1] == ';')
                add_rvar_node(h, 0, NULL, 0);
            else
                checkEnv(h, in + i, data);
        }
    }

    return i;
}

/**
 * replacedInput - Replaces string into variables.
 *
 * @head: Head of the linked list.
 * @input: Input string.
 * @newInput: New input string (replaced).
 * @nlen: New length.
 * Return: Replaced string.
 */
char *replacedInput(r_var **head, char *input, char *newInput, int nlen)
{
    r_var *indx;
    int i, j, k;

    indx = *head;
    for (j = i = 0; i < nlen; i++)
    {
        if (input[j] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val))
            {
                newInput[i] = input[j];
                j++;
            }
            else if (indx->len_var && !(indx->len_val))
            {
                for (k = 0; k < indx->len_var; k++)
                    j++;
                i--;
            }
            else
            {
                for (k = 0; k < indx->len_val; k++)
                {
                    newInput[i] = indx->val[k];
                    i++;
                }
                j += (indx->len_var);
                i--;
            }
            indx = indx->next;
        }
        else
        {
            newInput[i] = input[j];
            j++;
        }
    }

    return newInput;
}

/**
 * repVar - Calls functions to replace string into variables.
 *
 * @input: Input string.
 * @datash: Data structure.
 * Return: Replaced string.
 */
char *repVar(char *input, data_shell *datash)
{
    r_var *head, *indx;
    char *status, *newInput;
    int olen, nlen;

    status = aux_itoa(datash->status);
    head = NULL;

    olen = checkVariables(&head, input, status, datash);

    if (head == NULL)
    {
        free(status);
        return input;
    }

    indx = head;
    nlen = 0;

    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    newInput = malloc(sizeof(char) * (nlen + 1));
    newInput[nlen] = '\0';

    newInput = replacedInput(&head, input, newInput, nlen);

    free(input);
    free(status);
    free_rvar_list(&head);

    return newInput;
}
