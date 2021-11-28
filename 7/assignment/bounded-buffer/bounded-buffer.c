#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

// + Assignment: Allocate Semaphores
// -------------
sem_t mutex;
sem_t empty;
sem_t full;
// -------------

const int iterrations = 10;

const int bufferSize = 10;
buffer b;

void *producer(void *arg);
void *consumer(void *arg);

int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    buffer_init(&b, bufferSize);

    // + Assignment: Init Semaphores
    // -------------
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);
    // -------------

    pthread_t tProducer, tConsumer;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Execution
    pthread_create(&tProducer, &attr, producer, NULL);
    pthread_create(&tConsumer, &attr, consumer, NULL);

    pthread_join(tProducer, NULL);
    pthread_join(tConsumer, NULL);

    printf("-----------\n");
    printf("Buffer must have 0 items.\nYou have: %d items in buffer\nResult: ", b.current);
    if (b.current > 0)
    {
        printf("Failed!\n");
    }
    else
    {
        printf("Passed!\n");
    }

    // + Assignment: Clean up Semaphores
    // -------------
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    // -------------

    pthread_attr_destroy(&attr);
    buffer_destroy(&b);

    return 0;
}

void *producer(void *arg)
{
    for (int i = 0; i < iterrations; i++)
    {
        int value = rand() % 100;

        // + Assignment: Add to buffer
        // -------------
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer_add(&b, value);
        printf("Producer: + Added \"%d\" to buffer\n", value);

        sem_post(&mutex);
        sem_post(&full);
        // -------------
    }
}

void *consumer(void *arg)
{
    for (int i = 0; i < iterrations; i++)
    {
        // + Assignment: Remove from the buffer
        // -------------
        sem_wait(&full);
        sem_wait(&mutex);

        int value = buffer_remove(&b);
        printf("Consumer: - Removed \"%d\" from buffer\n", value);

        sem_post(&mutex);
        sem_post(&empty);
        // -------------
    }
}