#include "main.h"

/**
 * aux_help_env - Display help information for the 'env' builtin.
 * Return: No return.
 */
void aux_help_env(void)
{
    const char *help = "env: env [option] [name=value] [command [args]]\n"
                       "\tPrint the environment of the shell.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_setenv - Display help information for the 'setenv' builtin.
 * Return: No return.
 */
void aux_help_setenv(void)
{
    const char *help = "setenv: setenv (const char *name, const char *value, int replace)\n"
                       "\tAdd a new definition to the environment.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_unsetenv - Display help information for the 'unsetenv' builtin.
 * Return: No return.
 */
void aux_help_unsetenv(void)
{
    const char *help = "unsetenv: unsetenv (const char *name)\n"
                       "\tRemove an entry completely from the environment.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_general - Entry point for general help information for the 'help' builtin.
 * Return: No return.
 */
void aux_help_general(void)
{
    const char *help = "^-^ bash, version 1.0(1)-release\n"
                       "These commands are defined internally. Type 'help' to see the list.\n"
                       "Type 'help name' to find out more about the function 'name'.\n\n"
                       " alias: alias [name=['string']]\n"
                       " cd: cd [-L|[-P [-e]] [-@]] [dir]\n"
                       " exit: exit [n]\n"
                       " env: env [option] [name=value] [command [args]]\n"
                       " setenv: setenv [variable] [value]\n"
                       " unsetenv: unsetenv [variable]\n";

    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_exit - Display help information for the 'exit' builtin.
 * Return: No return.
 */
void aux_help_exit(void)
{
    const char *help = "exit: exit [n]\n"
                       "Exit shell.\n"
                       "Exits the shell with a status of N. If N is omitted, the exit status is that of the last command executed.\n";

    write(STDOUT_FILENO, help, _strlen(help));
}
