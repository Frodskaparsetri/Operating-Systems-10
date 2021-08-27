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

    pid_t pid = fork();
    if (pid == 0)
    {
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

            printf("%d ", number);
        }
        printf("\n");
        return 0;
    }

    if (pid < 0)
    {
        fprintf(stderr, "failed to create child");
        return -1;
    }

    wait(NULL);

    return 0;
}