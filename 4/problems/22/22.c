#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int average;
int minimum;
int maximum;

void *calculateAverage(void *param);
void *calculateMin(void *param);
void *calculateMax(void *param);

struct NumberCrunch
{
    int *numbers;
    int count;
};

// ARGS: A space seperated list of numbers
int main(int argc, char *argv[])
{
    // Parse the args into a list of numbers
    int startingArg = 1;
    int argCountWithoutFirstArg = argc - startingArg;

    struct NumberCrunch params;
    params.count = argCountWithoutFirstArg;
    params.numbers = malloc(argCountWithoutFirstArg * sizeof(int));
    for (int i = startingArg, j = 0; i < argc; i++, j++)
    {
        params.numbers[j] = atoi(argv[i]);
    }

    // Threading code
    pthread_t tid[3];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, calculateAverage, &params);
    pthread_create(&tid[1], &attr, calculateMin, &params);
    pthread_create(&tid[2], &attr, calculateMax, &params);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("The average value is %d\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    free(params.numbers);
    return 0;
}

void *calculateAverage(void *param)
{
    struct NumberCrunch *numbers = param;

    int sum = 0;
    for (int i = 0; i < numbers->count; i++)
    {
        sum += numbers->numbers[i];
    }

    average = sum / numbers->count;

    pthread_exit(0);
}

void *calculateMin(void *param)
{
    struct NumberCrunch *numbers = param;

    minimum = 100000;
    for (int i = 0; i < numbers->count; i++)
    {
        if (numbers->numbers[i] < minimum)
        {
            minimum = numbers->numbers[i];
        }
    }

    pthread_exit(0);
}
void *calculateMax(void *param)
{
    struct NumberCrunch *numbers = param;

    maximum = -10000;
    for (int i = 0; i < numbers->count; i++)
    {
        if (numbers->numbers[i] > maximum)
        {
            maximum = numbers->numbers[i];
        }
    }

    pthread_exit(0);
}