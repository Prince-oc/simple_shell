#include "main.h"

/**
 * readLine - Reads the input string.
 *
 * @i_eof: Return value of getline function.
 * Return: Input string.
 */
char *readLine(int *i_eof)
{
    char *input = NULL;
    size_t bufsize = 0;

    // Using getline to read input from stdin
    ssize_t chars_read = getline(&input, &bufsize, stdin);

    if (chars_read == -1)
    {
        // Handle error or end of file
        if (feof(stdin))
        {
            // End of file reached
            *i_eof = -1;
        }
        else
        {
            // An error occurred
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Set the return value of getline
        *i_eof = chars_read;
    }

    return input;
}
