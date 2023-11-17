#include "main.h"

/**
 * _memcpy - Copies information between void pointers.
 * @dest: Destination pointer.
 * @src: Source pointer.
 * @size: Size of the new pointer.
 *
 * Return: No return.
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
    char *char_dest = (char *)dest;
    const char *char_src = (const char *)src;
    unsigned int i;

    for (i = 0; i < size; i++)
    {
        char_dest[i] = char_src[i];
    }
}

/**
 * _realloc - Reallocates a memory block.
 * @ptr: Pointer to the memory previously allocated.
 * @old_size: Size, in bytes, of the allocated space of ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: Pointer to the reallocated memory block.
 * If new_size == old_size, returns ptr without changes.
 * If malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *newptr;

    if (ptr == NULL)
    {
        return malloc(new_size);
    }

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
    {
        return ptr;
    }

    newptr = malloc(new_size);
    if (newptr == NULL)
    {
        return NULL;
    }

    if (new_size < old_size)
    {
        _memcpy(newptr, ptr, new_size);
    }
    else
    {
        _memcpy(newptr, ptr, old_size);
    }

    free(ptr);
    return newptr;
}

/**
 * _reallocdp - Reallocates a memory block of a double pointer.
 * @ptr: Double pointer to the memory previously allocated.
 * @old_size: Size, in bytes, of the allocated space of ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: Double pointer to the reallocated memory block.
 * If new_size == old_size, returns ptr without changes.
 * If malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    if (ptr == NULL)
    {
        return malloc(sizeof(char *) * new_size);
    }

    if (new_size == old_size)
    {
        return ptr;
    }

    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
    {
        return NULL;
    }

    for (i = 0; i < old_size; i++)
    {
        newptr[i] = ptr[i];
    }

    free(ptr);

    return newptr;
}
