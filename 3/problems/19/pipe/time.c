#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define READ_END 0
#define WRITE_END 1
#define PIPE_CREATION_FAILED -1
#define IS_CHILD_PROCESS 0

int main(int argc, char *argv[])
{
    const int bufferSize = sizeof(struct timeval);
    int fd[2];

    if (pipe(fd) == PIPE_CREATION_FAILED)
    {
        fprintf(stderr, "Fork failed");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "failed to create child process");
        return -1;
    }

    // Child Process
    if (pid == IS_CHILD_PROCESS)
    {
        close(fd[READ_END]);

        struct timeval current;

        gettimeofday(&current, NULL);

        write(fd[WRITE_END], &current, sizeof(struct timeval));
        close(fd[WRITE_END]);

        return 0;
    }

    wait(NULL);

    struct timeval startTime;
    close(fd[WRITE_END]);
    read(fd[READ_END], &startTime, sizeof(struct timeval));
    close(fd[READ_END]);

    struct timeval endTime;
    gettimeofday(&endTime, NULL);

    int startMcrs = startTime.tv_usec;
    int endMcrs = endTime.tv_usec;

    int elapsedMcrs = endMcrs - startMcrs;
    float elapsedSeconds = elapsedMcrs / 1000000.0f;

    printf("Elapsed Time: %fs\n", elapsedSeconds);

    return 0;
}