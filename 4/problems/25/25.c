#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numerOfPointsInCircle;

void *calculateNumberOfPointsInsideCircle(void *param);
int randomNumber(int min, int max);

// gcc -fopenmp 25.c -o 25 && ./25

// ARGS: single number (number of iterations)
int main(int argc, char *argv[])
{
    int interationCount = atoi(argv[1]);

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, calculateNumberOfPointsInsideCircle, &interationCount);

    pthread_join(tid, NULL);

    float pi = 4.0f * numerOfPointsInCircle / interationCount;

    printf("Estimated Pi: %f\n", pi);
    printf("Pi: %f\n", 3.14159265359);

    return 0;
}

void *calculateNumberOfPointsInsideCircle(void *param)
{
    int *input = param;
    int iterationCount = *input;

    // Generate Random points
    for (int i = 0; i < iterationCount; i++)
    {
        float x = randomNumber(-100, 100) / 100.0f;
        float y = randomNumber(-100, 100) / 100.0f;

        // http://toreaurstad.blogspot.com/2015/07/calculating-pi-in-c-using-monte-carlo.html
        // in the MonteCarloPiApproximationParallelTasksSimulation function

        if (sqrt(x * x + y * y) <= 1.0)
        {
            numerOfPointsInCircle++;
        }
    }

    pthread_exit(0);
}

int randomNumber(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}