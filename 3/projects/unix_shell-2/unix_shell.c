#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

void parseArgsFromString(const char *input, char **args);

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */

    int should_run = 1; /* flag to determine when to exit program */

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        char input[MAX_LINE];
        scanf("%[^\n]%c*", input);

        /**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) parent will invoke wait() unless command included & */
    }
    return 0;
}

void parseArgsFromString(const char *input, char **args)
{
    char *ptr = strtok(input, " ");

    int i = 0;
    while (ptr != NULL)
    {
        args[i++] = ptr;
        ptr = strtok(NULL, " ");
    }
}