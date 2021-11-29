#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int philosopherCount = 5;
int amountOfRice = 20;
const int maxThinkingTimeUs = 1000000 / 3;

// + Assignment: Allocate Semaphores
// -------------

// -------------

void *philosopher(void *args);

int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    pthread_t tPhilosophers[philosopherCount];
    size_t philosopherIds[philosopherCount];

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // + Assignment: Init Semaphores
    // -------------
    for (int i = 0; i < philosopherCount; i++)
    {
        philosopherIds[i] = i + 1;
    }
    // -------------

    // Execution
    for (int i = 0; i < philosopherCount; i++)
    {
        pthread_create(&tPhilosophers[i], &attr, philosopher, (void *)&philosopherIds[i]);
    }

    for (int i = 0; i < philosopherCount; i++)
    {
        pthread_join(tPhilosophers[i], NULL);
    }

    // + Assignment: Clean up Semaphores
    // -------------

    // -------------

    return 0;
}

void *philosopher(void *args)
{
    int philosopherId = *((int *)args);

    while (amountOfRice > 0)
    {
        printf("Philosopher %d: Thinking...\n", philosopherId);

        int thinkingTime = rand() % maxThinkingTimeUs;
        usleep(maxThinkingTimeUs);

        // + Assignment: Eat
        // -------------

        amountOfRice--;
        printf("Philosopher %d: Ate\tRice left: %d \n", philosopherId, amountOfRice);

        // -------------
    }
    pthread_exit(0);
}