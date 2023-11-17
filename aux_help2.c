#include "main.h"

/**
 * aux_help - Display help information for the builtin 'help'.
 * Return: No return.
 */
void aux_help(void)
{
    const char *help = "help: help [-dms] [pattern ...]\n"
                       "\tDisplay information about builtin commands.\n"
                       "\tDisplays brief summaries of builtin commands.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_alias - Display help information for the builtin 'alias'.
 * Return: No return.
 */
void aux_help_alias(void)
{
    const char *help = "alias: alias [-p] [name[=value]...]\n"
                       "\tDefine or display aliases.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_cd - Display help information for the builtin 'cd'.
 * Return: No return.
 */
void aux_help_cd(void)
{
    const char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n"
                       "\tChange the shell working directory.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}
