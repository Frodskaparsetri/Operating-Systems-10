#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numerOfPointsInCircle;

void *calculateNumberOfPointsInsideCircle(void *param);
int randomNumber(int min, int max);

// ARGS: single number (number of iterations)
int main(int argc, char *argv[])
{
    // NOTE: the first element in the argv, is the name of the execution path
    // i.e. if you executed ./my-dir/my-app. then the argc would be "./my-dir/my-app"
    const int skipExecutableArgName = 1;
    if (argc - skipExecutableArgName <= 0)
    {
        printf("ERROR: You need to specify a number of iterations \n");
        return 1;
    }

    int iterationCount = atoi(argv[skipExecutableArgName]);

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, calculateNumberOfPointsInsideCircle, &iterationCount);

    pthread_join(tid, NULL);

    float pi = 4.0f * numerOfPointsInCircle / iterationCount;

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