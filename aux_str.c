#include "main.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
    int i, j;

    for (i = 0; dest[i] != '\0'; i++)
        ;

    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }

    dest[i] = '\0';
    return dest;
}

/**
 * _strcpy - Copies a string.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, const char *src)
{
    size_t a;

    for (a = 0; src[a] != '\0'; a++)
    {
        dest[a] = src[a];
    }
    dest[a] = '\0';

    return dest;
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: 0 if strings are equal, positive if s1 is greater, negative if s2 is greater.
 */
int _strcmp(const char *s1, const char *s2)
{
    int i;

    for (i = 0; s1[i] == s2[i] && s1[i] != '\0'; i++)
        ;

    if (s1[i] > s2[i])
        return 1;
    if (s1[i] < s2[i])
        return -1;
    return 0;
}

/**
 * _strchr - Locates a character in a string.
 * @s: String.
 * @c: Character.
 * Return: Pointer to the first occurrence of the character c, or NULL if not found.
 */
char *_strchr(const char *s, int c)
{
    while (*s != (char)c)
    {
        if (*s == '\0')
            return NULL;
        s++;
    }

    return (char *)s;
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: Initial segment.
 * @accept: Accepted bytes.
 * Return: The number of accepted bytes.
 */
size_t _strspn(const char *s, const char *accept)
{
    size_t i, j;

    for (i = 0; s[i] != '\0'; i++)
    {
        int bool = 1;

        for (j = 0; accept[j] != '\0'; j++)
        {
            if (s[i] == accept[j])
            {
                bool = 0;
                break;
            }
        }

        if (bool == 1)
            break;
    }

    return i;
}
