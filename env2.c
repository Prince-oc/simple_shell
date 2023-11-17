#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(const char *name, const char *value)
{
    int len_name = _strlen(name);
    int len_value = _strlen(value);
    int len = len_name + len_value + 2;

    char *new = malloc(sizeof(char) * len);
    if (new == NULL) {
        perror("copy_info malloc");
        exit(EXIT_FAILURE);
    }

    _strcpy(new, name);
    _strcat(new, "=");
    _strcat(new, value);

    return new;
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(const char *name, const char *value, data_shell *datash)
{
    int i;
    char *var_env, *name_env;

    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");
        if (_strcmp(name_env, name) == 0)
        {
            free(datash->_environ[i]);
            datash->_environ[i] = copy_info(name_env, value);
            free(var_env);
            return;
        }
        free(var_env);
    }

    datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
    datash->_environ[i] = copy_info(name, value);
    datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{
    if (datash->args[1] == NULL || datash->args[2] == NULL)
    {
        get_error(datash, -1);
        return 1;
    }

    set_env(datash->args[1], datash->args[2], datash);

    return 1;
}

/**
 * _unsetenv - deletes an environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
    char **realloc_environ;
    char *var_env, *name_env;
    int i, j, k;

    if (datash->args[1] == NULL)
    {
        get_error(datash, -1);
        return 1;
    }

    k = -1;
    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");
        if (_strcmp(name_env, datash->args[1]) == 0)
        {
            k = i;
        }
        free(var_env);
    }

    if (k == -1)
    {
        get_error(datash, -1);
        return 1;
    }

    realloc_environ = malloc(sizeof(char *) * i);
    if (realloc_environ == NULL)
    {
        perror("_unsetenv malloc");
        exit(EXIT_FAILURE);
    }

    for (i = j = 0; datash->_environ[i]; i++)
    {
        if (i != k)
        {
            realloc_environ[j] = datash->_environ[i];
            j++;
        }
    }

    realloc_environ[j] = NULL;
    free(datash->_environ[k]);
    free(datash->_environ);
    datash->_environ = realloc_environ;

    return 1;
}
