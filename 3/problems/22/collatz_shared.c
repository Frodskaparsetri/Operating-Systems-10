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
    int number = 0;

    if (argv[1] == NULL)
    {
        fprintf(stderr, "Specify a number!\n");
        return -1;
    }

    sscanf(argv[1], "%d", &number);
    if (number < 0)
    {
        fprintf(stderr, "Positive numbers only!\n");
        return -1;
    }

    const int size = sizeof(int) * 10;
    const char *name = "COLLATZ";

    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, size);
    int *ptr = (int *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid_t pid = fork();
    if (pid == 0)
    {
        int i = 0;
        while (number > 1)
        {
            if (number % 2 == 0)
            {
                number /= 2;
            }
            else
            {
                number = 3 * number + 1;
            }
            ptr[i++] = number;
        }

        shm_unlink(name);
        return 0;
    }

    if (pid < 0)
    {
        fprintf(stderr, "failed to create child");
        return -1;
    }

    wait(NULL);

    int i = 0;
    while (ptr[i++] > 1)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    return 0;
}