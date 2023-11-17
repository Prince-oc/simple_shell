/**
 * handle_sigint - Signal handler for Ctrl+C in the prompt
 * @signal: Signal number
 */
void handle_sigint(int signal)
{
    (void)signal;  // Avoid unused parameter warning
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
