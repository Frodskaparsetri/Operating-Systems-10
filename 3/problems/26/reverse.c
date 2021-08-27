#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1
#define PIPE_CREATION_FAILED -1
#define IS_CHILD_PROCESS 0
#define BUFFER_SIZE 4096

void reverseCase(char *message, int size);

int main(void)
{
    int fd[2];

    char *message = "Hi there!";
    int messageSize = strlen(message) + 1;

    if (pipe(fd) == PIPE_CREATION_FAILED)
    {
        fprintf(stderr, "Pipe creation failed!");
        return -1;
    }

    printf("Original Message: %s\n", message);

    write(fd[WRITE_END], message, messageSize);

    int pid = fork();
    if (pid == 0)
    {
        printf("Child Reversing...\n");

        char readMessage[messageSize];

        read(fd[READ_END], readMessage, messageSize);

        reverseCase(readMessage, messageSize);

        write(fd[WRITE_END], readMessage, messageSize);

        printf("Child Reversed!\n");

        return 0;
    }

    if (pid < 0)
    {
        fprintf(stderr, "Failed to create child process\n");
        return -1;
    }

    wait(NULL);

    char reversedMessage[messageSize];

    read(fd[READ_END], &reversedMessage, messageSize);

    printf("Reversed Message: %s\n", reversedMessage);

    return 0;
}

void reverseCase(char *message, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        char character = message[i];
        if (islower(character))
        {
            character = toupper(character);
        }
        else
        {
            character = tolower(character);
        }

        message[i] = character;
    }
}