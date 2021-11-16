#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *printPreceedingPrimeNumbers(void *param);

// ARGS: A single number
int main(int argc, char *argv[])
{
    // NOTE: the first element in the argv, is the name of the execution path
    // i.e. if you executed ./my-dir/my-app. then the argc would be "./my-dir/my-app"
    const int skipExecutableArgName = 1;
    if (argc - skipExecutableArgName <= 0)
    {
        printf("ERROR: You need to specify a number to generate the preceeding prime numbers\n");
        return 1;
    }

    char *topPrimeNumber = argv[skipExecutableArgName];

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, printPreceedingPrimeNumbers, topPrimeNumber);

    pthread_join(tid, NULL);
    return 0;
}

void *printPreceedingPrimeNumbers(void *param)
{
    const unsigned int topNumber = atoi(param);

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