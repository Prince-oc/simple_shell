#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
    int length = 0;
    char temp;

    // Find the length of the string
    while (s[length] != '\0')
    {
        length++;
    }

    // Reverse the string using two pointers
    for (int start = 0, end = length - 1; start < end; start++, end--)
    {
        // Swap characters at start and end positions
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
    }
}
