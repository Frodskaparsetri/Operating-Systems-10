#include <stdio.h>

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    const int size = sizeof(struct timeval);
    const char *name = "TIME";

    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, size);
    struct timeval *ptr = (struct timeval *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid_t pid = fork();
    if (pid == 0)
    {
        gettimeofday(ptr, NULL);

        // it starts at 1, because the first value is the name of the program (i.e. "time")
        execvp(argv[1], argv + 1);

        shm_unlink(name);
        return 0;
    }

    wait(NULL);

    struct timeval current;
    gettimeofday(&current, NULL);

    suseconds_t startMcrs = ptr->tv_usec;
    suseconds_t endMcrs = current.tv_usec;

    suseconds_t elapsedMcrs = endMcrs - startMcrs;

    // convert microseconds to seconds
    float elapsedSeconds = elapsedMcrs / 1000000.0f;

    // // long int elapsed = endSeconds - startSeconds;
    printf("Elapsed time: %fs\n", elapsedSeconds);

    return 0;
}