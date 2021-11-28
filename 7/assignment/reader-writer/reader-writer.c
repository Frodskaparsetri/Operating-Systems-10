#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// + Assignment: Allocate Semaphores
// -------------
sem_t mutex;
sem_t wrt;
int readCount;
// -------------

int database = 5;
const int writerSleepTimeUs = 1000000 / 3;
const int readerSleepTimeUs = 1000000 / 3;

void *
writer(void *args);
void *reader(void *args);

int main(int argc, char **argv)
{
    // init
    time_t t;
    srand((unsigned)time(&t));

    const int readerId1 = 1;
    const int readerId2 = 2;

    pthread_t tWriter, tReader1, tReader2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    // + Assignment: Init Semaphores
    // -------------
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readCount = 0;
    // -------------

    // execute
    pthread_create(&tWriter, &attr, writer, NULL);
    pthread_create(&tReader1, &attr, reader, (void *)&readerId1);
    pthread_create(&tReader2, &attr, reader, (void *)&readerId2);

    pthread_join(tWriter, NULL);
    pthread_join(tReader1, NULL);
    pthread_join(tReader2, NULL);

    // clear
    pthread_attr_destroy(&attr);

    // + Assignment: Clean up Semaphores
    // -------------
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    // -------------

    return 0;
}

void *writer(void *args)
{

    while (1)
    {
        usleep(writerSleepTimeUs);
        int value = rand() % 100;

        // + Assignment: Write to "Database"
        // -------------
        sem_wait(&wrt);
        database = value;
        sem_post(&wrt);
        // -------------

        printf("------\nWriter: wrote \"%d\" to database\n", value);
    }
}

void *reader(void *args)
{
    int readerId = *((int *)args);
    while (1)
    {
        // + Assignment: Read from "Database"
        // -------------
        sem_wait(&mutex);
        readCount++; // the number of readers has now increased by 1

        if (readCount >= 1)
        {
            sem_wait(&wrt);   // this ensures no writer can enter if there is 1+ readers
            sem_post(&mutex); // other readers can enter while the currend read is inside the critical section
        }

        printf("Reader %d: read \"%d\" to database\n", readerId, database);

        sem_wait(&mutex);
        readCount--; // a reader wants to leave

        if (readCount <= 0) // no reader is left in the critical section
        {
            sem_post(&wrt);   // writers can enter
            sem_post(&mutex); // reader leaves
        }
        // -------------

        usleep(readerSleepTimeUs);
    }
}