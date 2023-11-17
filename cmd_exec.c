#include "main.h"

/**
 * is_cdir - checks ":" if it is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
    if (path[*i] == ':')
        return 1;

    while (path[*i] != ':' && path[*i])
    {
        *i += 1;
    }

    if (path[*i])
        *i += 1;

    return 0;
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
    char *path, *ptr_path, *token_path, *dir;
    int len_dir, len_cmd, i;
    struct stat st;

    path = _getenv("PATH", _environ);
    if (!path)
        return NULL;

    ptr_path = _strdup(path);
    len_cmd = _strlen(cmd);
    token_path = _strtok(ptr_path, ":");
    i = 0;
    while (token_path != NULL)
    {
        if (is_cdir(path, &i))
        {
            if (stat(cmd, &st) == 0)
            {
                free(ptr_path);
                return cmd;
            }
        }

        len_dir = _strlen(token_path);
        dir = malloc(len_dir + len_cmd + 2);
        _strcpy(dir, token_path);
        _strcat(dir, "/");
        _strcat(dir, cmd);
        _strcat(dir, "\0");

        if (stat(dir, &st) == 0)
        {
            free(ptr_path);
            return dir;
        }

        free(dir);
        token_path = _strtok(NULL, ":");
    }

    free(ptr_path);
    if (stat(cmd, &st) == 0)
        return cmd;

    return NULL;
}

/**
 * is_executable - determines if it is an executable
 *
 * @datash: data structure
 * Return: 0 if it is not an executable, other number if it does
 */
int is_executable(data_shell *datash)
{
    struct stat st;
    int i;
    char *input;

    input = datash->args[0];
    for (i = 0; input[i]; i++)
    {
        if (input[i] == '.')
        {
            if (input[i + 1] == '.')
                return 0;
            if (input[i + 1] == '/')
                continue;
            else
                break;
        }
        else if (input[i] == '/' && i != 0)
        {
            if (input[i + 1] == '.')
                continue;
            i++;
            break;
        }
        else
            break;
    }

    if (i == 0)
        return 0;

    if (stat(input + i, &st) == 0)
    {
        return i;
    }

    get_error(datash, 127);
    return -1;
}

/**
 * check_error_cmd - verifies if the user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data_shell *datash)
{
    if (dir == NULL)
    {
        get_error(datash, 127);
        return 1;
    }

    if (_strcmp(datash->args[0], dir) != 0)
    {
        if (access(dir, X_OK) == -1)
        {
            get_error(datash, 126);
            free(dir);
            return 1;
        }

        free(dir);
    }
    else
    {
        if (access(datash->args[0], X_OK) == -1)
        {
            get_error(datash, 126);
            return 1;
        }
    }

    return 0;
}

/**
 * cmd_exec - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
    pid_t pid;
    pid_t wait_pid;
    int state;
    int exec;
    char *executable_path;

    exec = is_executable(datash);
    if (exec == -1)
        return 1;

    if (exec == 0)
    {
        executable_path = _which(datash->args[0], datash->_environ);
        if (check_error_cmd(executable_path, datash) == 1)
            return 1;
    }
    else
    {
        executable_path = datash->args[0];
    }

    pid = fork();
    if (pid == 0)
    {
        execve(executable_path + exec, datash->args, datash->_environ);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else
    {
        do
        {
            wait_pid = waitpid(pid, &state, WUNTRACED);
        } while (!WIFEXITED(state) && !WIFSIGNALED(state));
    }

    datash->status = state / 256;
    return 1;
}
