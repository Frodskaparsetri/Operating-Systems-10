#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80
#define TRUE 1
#define FALSE 0
#define STRINGS_MATCH 0
#define IS_CHILD_PROCESS 0

#define EXIT "exit"
#define CONCURRENT_IDENTIFIER "&"
#define REPEAT_PREVIOUS_IDENTIFIER "!!"

#define REDIRECT_OUT ">"
#define REDIRECT_IN "<"

void cloneArguments(char **original, char **clone, int argCount);
int stringEqual(const char *left, const char *right);

int main(void)
{
    int should_run = TRUE;

    int argCount = 0;
    char *args[MAX_LINE / 2 + 1];

    char *token;

    char prevInput[MAX_LINE] = {0};

    int defaultStdOut = dup(STDOUT_FILENO);
    int defaultStdIn = dup(STDIN_FILENO);

    char *redirect = 0;
    char *redirectTo;

    while (should_run)
    {
        /* --- User Input --- */
        printf("osh> ");
        fflush(stdout);

        // read user input
        char input[MAX_LINE];
        int inputCount = scanf("%[^\n]", input);
        scanf("%*c"); // <-- this is to clear the trailing \n

        // if no input was found then simply continue requesting user input
        if (inputCount == 0)
        {
            continue;
        }

        // if the user uses the history command,
        // then change the input target to be the previous input
        char *inputTarget;
        if (strcmp(input, REPEAT_PREVIOUS_IDENTIFIER) == STRINGS_MATCH)
        {
            // if there is no history, then simply continue requesting user input
            if (!prevInput[0])
            {
                continue;
            }

            inputTarget = prevInput;
        }
        else
        {
            inputTarget = input;
            strcpy(prevInput, input); // <-- keep history of the input
        }

        // parse user input into command and command arguments
        argCount = 0;
        int executeConcurrently = FALSE;
        char *token = strtok(inputTarget, " ");
        while (token != NULL)
        {
            // check to see if there is a concurrency symbol. if there is, then execute the command concurrently
            if (stringEqual(token, CONCURRENT_IDENTIFIER))
            {
                executeConcurrently = TRUE;
            }
            // check to see if the user tries to redirect the output to a file
            else if (stringEqual(token, REDIRECT_OUT))
            {
                token = strtok(NULL, " "); // <-- grab the next argument (which should be the file)
                int fd = open(token, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            // check to see if the user tries to redirect arguments from a file
            else if (stringEqual(token, REDIRECT_IN))
            {
                token = strtok(NULL, " "); // <-- grab the next argument (which should be the file)
                int fd = open(token, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            else
            {
                args[argCount++] = token;
            }

            token = strtok(NULL, " ");
        }

        // because of how execvp works, the last argument needs to be a terminating NULL
        // https://stackoverflow.com/a/6274209
        args[argCount] = NULL;

        // check to see if the user's command was exit; if so then terminate.
        if (strcmp(args[0], EXIT) == STRINGS_MATCH)
        {
            should_run = FALSE;
            continue;
        }

        /* --- Input Execution --- */
        // Start Child Process
        pid_t pid = fork();
        if (pid == IS_CHILD_PROCESS)
        {
            int execStatus = execvp(args[0], args);

            if (execStatus < 0)
            {
                printf("Failed to execute\n");
                return -1;
            }

            return 0;
        }

        if (pid < 0)
        {
            printf("Failed to create child process");
            return -1;
        }

        if (!executeConcurrently)
        {
            wait(NULL);
        }

        // reset back to the original output, when we're done
        dup2(defaultStdOut, STDOUT_FILENO);
        dup2(defaultStdIn, STDIN_FILENO);
    }

    close(defaultStdOut);
    close(defaultStdIn);
    return 0;
}

void cloneArguments(char **original, char **clone, int argCount)
{
    for (int i = 0; i < argCount; i++)
    {
        strcpy(clone[i], original[i]);
    }
}

int stringEqual(const char *left, const char *right)
{
    if (strcmp(left, right) == STRINGS_MATCH)
    {
        return TRUE;
    }

    return FALSE;
}