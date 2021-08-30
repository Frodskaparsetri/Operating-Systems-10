#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numerOfPointsInCircle;

int randomNumber(int min, int max);

// ARGS: single number (number of iterations)
int main(int argc, char *argv[])
{
    int iterationCount = atoi(argv[1]);

#pragma omp parallel for
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

    float pi = 4.0f * numerOfPointsInCircle / iterationCount;

    printf("Estimated Pi: %f\n", pi);
    printf("Pi: %f\n", 3.14159265359);

    return 0;
}

int randomNumber(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}