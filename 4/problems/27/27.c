#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

size_t *fibonachiNumbers;

void *calculateFibonachiNumbers(void *param);

// ARGS: single number (number of fibonachi sequences)
int main(int argc, char *argv[])
{
    // confirm with:
    // https://www.omnicalculator.com/math/fibonacci

    /* adding a count, so it adds up to the amount the user specified 
    and not based on the array - i.e. from index 0 */
    int numberOfFibonachiSequences = atoi(argv[1]) + 1;

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, calculateFibonachiNumbers, &numberOfFibonachiSequences);

    pthread_join(tid, NULL);

    printf("%d Fibonachi numbers:\n", numberOfFibonachiSequences);
    printf("------\n");
    for (int i = 0; i < numberOfFibonachiSequences; i++)
    {
        printf("%lu\n", fibonachiNumbers[i]);
    }

    free(fibonachiNumbers);
    return 0;
}

void *calculateFibonachiNumbers(void *param)
{
    int *input = param;
    int count = *input;

    int i = 0;
    fibonachiNumbers = (size_t *)malloc(count * sizeof(size_t));
    fibonachiNumbers[i++] = 0;
    fibonachiNumbers[i++] = 1;

    for (; i <= count; i++)
    {
        fibonachiNumbers[i] = fibonachiNumbers[i - 2] + fibonachiNumbers[i - 1];
    }

    pthread_exit(0);
}