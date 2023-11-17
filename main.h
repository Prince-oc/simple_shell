#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

typedef struct DataShell {
    char **av;
    char *input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} DataShell;

typedef struct SeparatorNode {
    char separator;
    struct SeparatorNode *next;
} SeparatorNode;

typedef struct LineNode {
    char *line;
    struct LineNode *next;
} LineNode;

typedef struct VariableNode {
    int len_var;
    char *val;
    int len_val;
    struct VariableNode *next;
} VariableNode;

typedef struct BuiltinCommand {
    char *name;
    int (*function)(DataShell *data);
} BuiltinCommand;

SeparatorNode *addSeparatorNodeEnd(SeparatorNode **head, char sep);
void freeSeparatorList(SeparatorNode **head);

LineNode *addLineNodeEnd(LineNode **head, char *line);
void freeLineList(LineNode **head);

VariableNode *addVariableNode(VariableNode **head, int lvar, char *var, int lval);
void freeVariableList(VariableNode **head);

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

char *_strdup(const char *s);
int _strlen(const char *s);
int cmpChars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

void reverseString(char *s);

int repeatedChar(char *input, int i);
int errorSepOp(char *input, int i, char last);
int firstChar(char *input, int *i);
void printSyntaxError(DataShell *data, char *input, int i, int bool);
int checkSyntaxError(DataShell *data, char *input);

char *withoutComment(char *in);
void shellLoop(DataShell *data);

char *readLine(int *iEof);

char *swapChar(char *input, int bool);
void addNodes(SeparatorNode **headS, LineNode **headL, char *input);
void goNext(SeparatorNode **listS, LineNode **listL, DataShell *data);
int splitCommands(DataShell *data, char *input);
char **splitLine(char *input);

void checkEnv(VariableNode **h, char *in, DataShell *data);
int checkVars(VariableNode **h, char *in, char *st, DataShell *data);
char *replacedInput(VariableNode **head, char *input, char *newInput, int nlen);
char *repVar(char *input, DataShell *data);

void bringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

int execLine(DataShell *data);

int isCurrentDirectory(char *path, int *i);
char *_which(char *cmd, char **_environ);
int isExecutable(DataShell *data);
int checkErrorCmd(char *dir, DataShell *data);
int cmdExec(DataShell *data);

char *_getenv(const char *name, char **_environ);
int _env(DataShell *data);

char *copyInfo(char *name, char *value);
void setEnv(char *name, char *value, DataShell *data);
int _setenv(DataShell *data);
int _unsetenv(DataShell *data);

void cdDot(DataShell *data);
void cdTo(DataShell *data);
void cdPrevious(DataShell *data);
void cdToHome(DataShell *data);

int cdShell(DataShell *data);

int (*getBuiltin(char *cmd))(DataShell *data);

int exitShell(DataShell *data);

int getLen(int n);
char *auxItoa(int n);
int _atoi(char *s);

char *strcatCd(DataShell *data, char *cmd, char *msg, char *extra);
char *errorGetCd(DataShell *data);
char *errorNotFound(DataShell *data);
char *errorExitShell(DataShell *data);

char *errorGetAlias(char **args);
char *errorEnv(DataShell *data);
char *errorSyntax(char **args);
char *errorPermission(char **args);
char *errorPath126(DataShell *data);

int getError(DataShell *data, int eval);

void getSigint(int sig);

void auxHelpEnv(void);
void auxHelpSetenv(void);
void auxHelpUnsetenv(void);
void auxHelpGeneral(void);
void auxHelpExit(void);

void auxHelp(void);
void auxHelpAlias(void);
void auxHelpCd(void);

int getHelp(DataShell *data);

#endif
