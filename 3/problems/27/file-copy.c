#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1
#define PIPE_CREATION_FAILED -1
#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int fd[2];

    char *copyFrom = argv[1];
    char *copyTo = argv[2];

    FILE *file = fopen(copyFrom, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open \"%s\"\n", copyFrom);
        return -1;
    }
    printf("- \"%s\" opened\n", copyFrom);

    char fileContent[BUFFER_SIZE];
    fscanf(file, "%[^\0]", fileContent);

    printf("- content of file: \"%s\"\n", fileContent);

    fclose(file);

    if (pipe(fd) == PIPE_CREATION_FAILED)
    {
        fprintf(stderr, "Pipe creation failed!");
        return -1;
    }

    write(fd[WRITE_END], fileContent, BUFFER_SIZE);

    int pid = fork();
    if (pid == 0)
    {
        printf("-- Child process created!\n");

        char readMessage[BUFFER_SIZE];

        close(fd[WRITE_END]);
        read(fd[READ_END], readMessage, BUFFER_SIZE);

        FILE *newFile = fopen(copyTo, "w");
        if (newFile == NULL)
        {
            fprintf(stderr, "Failed to read or create file: \"%s\"\n", copyTo);
            return -1;
        }
        printf("-- \"%s\" opened or created!\n", copyTo);

        fprintf(newFile, "%s", readMessage);
        fclose(newFile);

        printf("-- content copied!\n");

        return 0;
    }

    if (pid < 0)
    {
        fprintf(stderr, "Failed to create child process\n");
        return -1;
    }

    wait(NULL);

    return 0;
}