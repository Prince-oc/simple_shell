#include "main.h"

/**
 * bring_line - Assigns the line variable for get_line
 * @lineptr: Buffer that stores the input string
 * @n: Size of line
 * @buffer: String that is passed to line
 * @j: Size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL || *n < j)
	{
		*n = (j > BUFSIZE) ? j : BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Read input from stream
 * @lineptr: Buffer that stores the input
 * @n: Size of lineptr
 * @stream: Stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	ssize_t retval;
	char *buffer;
	char t = 'z';
	static ssize_t input;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == NULL)
		return (-1);

	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}

		if (i == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = t;
		input++;
	}

	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;

	if (i != 0)
		input = 0;

	return (retval);
}
