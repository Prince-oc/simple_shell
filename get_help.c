#include "main.h"

/**
 * get_help - function that retrieves help messages according to the builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_shell *datash)
{
	char *builtin_commands[] = {"setenv", "env", "unsetenv", "help", "exit", "cd", "alias"};
	void (*help_functions[])() = {aux_help_setenv, aux_help_env, aux_help_unsetenv,
								   aux_help, aux_help_exit, aux_help_cd, aux_help_alias};

	for (int i = 0; i < sizeof(builtin_commands) / sizeof(builtin_commands[0]); i++)
	{
		if (_strcmp(datash->args[1], builtin_commands[i]) == 0)
		{
			help_functions[i]();
			datash->status = 0;
			return 1;
		}
	}

	write(STDERR_FILENO, datash->args[0], _strlen(datash->args[0]));
	datash->status = 0;
	return 1;
}
