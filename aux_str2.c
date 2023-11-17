#include "main.h"

/**
 * my_strdup - duplicates a string in the heap memory.
 * @source: Source string.
 * Return: Duplicated string.
 */
char *my_strdup(const char *source)
{
    if (source == NULL)
        return NULL;

    size_t length = _strlen(source);
    char *destination = malloc(sizeof(char) * (length + 1));

    if (destination == NULL)
        return NULL;

    _memcpy(destination, source, length + 1);
    return destination;
}

/**
 * my_strlen - Returns the length of a string.
 * @str: Input string.
 * Return: Length of the string.
 */
int my_strlen(const char *str)
{
    int length;

    for (length = 0; str[length] != '\0'; length++)
    {
    }
    return length;
}

/**
 * contains_delimiter - Checks if a string contains any characters from a set of delimiters.
 * @str: Input string.
 * @delimiters: Set of delimiters.
 * Return: 1 if the string contains delimiters, 0 otherwise.
 */
int contains_delimiter(char str[], const char *delimiters)
{
    unsigned int i, j, count;

    for (i = 0, count = 0; str[i] != '\0'; i++)
    {
        for (j = 0; delimiters[j] != '\0'; j++)
        {
            if (str[i] == delimiters[j])
            {
                count++;
                break;
            }
        }
    }

    return (i == count);
}

/**
 * my_strtok - Splits a string by a set of delimiters.
 * @str: Input string.
 * @delimiters: Set of delimiters.
 * Return: Pointer to the next token or NULL if there are no more tokens.
 */
char *my_strtok(char str[], const char *delimiters)
{
    static char *currentPosition, *endPosition;
    char *tokenStart;
    unsigned int i, hasToken;

    if (str != NULL)
    {
        if (contains_delimiter(str, delimiters))
            return NULL;

        currentPosition = str; // Store the first address
        i = my_strlen(str);
        endPosition = &str[i]; // Store the last address
    }

    tokenStart = currentPosition;

    if (tokenStart == endPosition) // Reached the end
        return NULL;

    for (hasToken = 0; *currentPosition; currentPosition++)
    {
        if (currentPosition != tokenStart && *currentPosition && *(currentPosition - 1) == '\0')
            break;

        for (i = 0; delimiters[i] != '\0'; i++)
        {
            if (*currentPosition == delimiters[i])
            {
                *currentPosition = '\0';
                if (currentPosition == tokenStart)
                    tokenStart++;
                break;
            }
        }

        if (hasToken == 0 && *currentPosition)
            hasToken = 1;
    }

    if (hasToken == 0) // String consists only of delimiters
        return NULL;

    return tokenStart;
}

/**
 * is_numeric - Defines if a string represents a number.
 * @str: Input string.
 * Return: 1 if the string is a number, 0 otherwise.
 */
int is_numeric(const char *str)
{
    unsigned int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }

    return 1;
}
