#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// + Assignment: Allocate Semaphores
// -------------

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

        printf("Reader %d: read \"%d\" to database\n", readerId, database);

        // -------------

        usleep(readerSleepTimeUs);
    }
}