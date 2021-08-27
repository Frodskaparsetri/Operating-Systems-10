#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *printPreceedingPrimeNumbers(void *param);

// ARGS: A single number
int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, printPreceedingPrimeNumbers, argv[1]);

    pthread_join(tid, NULL);
    return 0;
}

void *printPreceedingPrimeNumbers(void *param)
{
    int topNumber = atoi(param);

    printf("Preceeding Prime Numbers:\n");
    for (int i = topNumber; i > 0; i--)
    {
        if (i % 2 != 0)
        {
            printf("%d\n", i);
        }
    }

    pthread_exit(0);
}