#include "main.h"

/**
 * swap_special_chars - swaps | and & for non-printable chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_special_chars(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|' && input[i + 1] != '|')
				input[i] = 16;
			else if (input[i] == '&' && input[i + 1] != '&')
				input[i] = 12;
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
 * add_nodes_to_lists - add separators and command lines in the lists
 *
 * @head_sep: head of separator list
 * @head_lines: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes_to_lists(sep_list **head_sep, line_list **head_lines, char *input)
{
	int i;
	char *line;

	input = swap_special_chars(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_sep, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_sep, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_special_chars(line, 1);
		add_line_node_end(head_lines, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * move_to_next - move to the next command line stored
 *
 * @list_sep: separator list
 * @list_lines: command line list
 * @datash: data structure
 * Return: no return
 */
void move_to_next(sep_list **list_sep, line_list **list_lines, data_shell *datash)
{
	int loop_sep;
	sep_list *current_sep;
	line_list *current_line;

	loop_sep = 1;
	current_sep = *list_sep;
	current_line = *list_lines;

	while (current_sep != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (current_sep->separator == '&' || current_sep->separator == ';')
				loop_sep = 0;
			if (current_sep->separator == '|')
				current_line = current_line->next, current_sep = current_sep->next;
		}
		else
		{
			if (current_sep->separator == '|' || current_sep->separator == ';')
				loop_sep = 0;
			if (current_sep->separator == '&')
				current_line = current_line->next, current_sep = current_sep->next;
		}
		if (current_sep != NULL && !loop_sep)
			current_sep = current_sep->next;
	}

	*list_sep = current_sep;
	*list_lines = current_line;
}

/**
 * execute_commands - execute command lines according to separators
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int execute_commands(data_shell *datash, char *input)
{
	sep_list *head_sep, *current_sep;
	line_list *head_lines, *current_line;
	int loop;

	head_sep = NULL;
	head_lines = NULL;

	add_nodes_to_lists(&head_sep, &head_lines, input);

	current_sep = head_sep;
	current_line = head_lines;

	while (current_line != NULL)
	{
		datash->input = current_line->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		move_to_next(&current_sep, &current_line, datash);

		if (current_line != NULL)
			current_line = current_line->next;
	}

	free_sep_list(&head_sep);
	free_line_list(&head_lines);

	if (loop == 0)
		return 0;
	return 1;
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: array of tokens.
 */
char **split_line(char *input)
{
	size_t buffer_size = TOK_BUFSIZE;
	size_t i;
	char **tokens;
	char *token;

	tokens = malloc(sizeof(char *) * buffer_size);
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * buffer_size);
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
