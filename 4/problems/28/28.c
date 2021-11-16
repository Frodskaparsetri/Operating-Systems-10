#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define MIN_PID 300
#define MAX_PID 5000

#define FAILED -1
#define SUCCESSFUL 1

#define FAILED_TO_CREATE_PID -1
#define FAILED_TO_KILL_PID -1

typedef struct
{
    char *map;
    int min;
    int max;
    int size;
    int current;
    int availableCount;
    char free;
    char occupied;
} Pidmap;

Pidmap pidmap;

int allocate_map();
int allocate_pid();
int release_pid(int pid);

// Thread test code:
#define TREAD_COUNT 100
#define MIN_SLEEP_TIME 1
#define MAX_SLEEP_TIME 10

void *pidAllocatorTest(void *param);
int randomNumber(int min, int max);

int main(void)
{
    if (allocate_map() == FAILED)
    {
        fprintf(stderr, "Failed to allocate pidmap");
        return -1;
    }

    pthread_t tids[TREAD_COUNT];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    for (int i = 0; i < TREAD_COUNT; i++)
    {
        pthread_create(&tids[i], &attr, pidAllocatorTest, NULL);
    }

    for (int i = 0; i < TREAD_COUNT; i++)
    {
        pthread_join(tids[i], NULL);
    }

    return 0;
}

int allocate_map()
{
    pidmap.max = MAX_PID;
    pidmap.min = MIN_PID;
    pidmap.size = MAX_PID - MIN_PID;
    pidmap.availableCount = pidmap.size;

    pidmap.free = '0';
    pidmap.occupied = '1';

    pidmap.map = malloc(pidmap.size);
    for (int i = 0; i < pidmap.size; i++)
    {
        pidmap.map[i] = pidmap.free;
    }

    return SUCCESSFUL;
}

int allocate_pid()
{
    if (pidmap.availableCount <= 0)
    {
        pidmap.availableCount = 0;
        return FAILED;
    }

    for (; pidmap.current < pidmap.size; pidmap.current++)
    {
        if (pidmap.map[pidmap.current] == pidmap.free)
        {
            pidmap.map[pidmap.current] = pidmap.occupied;
            pidmap.availableCount--;

            int pid = pidmap.current + pidmap.min;
            pidmap.current++;

            printf("Allocated PID: %d\n", pid);
            return pid;
        }
    }

    pidmap.current = 0;
    return allocate_pid();
}

int release_pid(int pid)
{
    int pidmapIndex = pid - pidmap.min;
    if (pidmapIndex > pidmap.size - 1 || pidmapIndex < 0)
    {
        return FAILED;
    }

    if (pidmap.map[pidmapIndex] != pidmap.occupied)
    {
        return FAILED;
    }

    pidmap.map[pidmapIndex] = pidmap.free;
    pidmap.availableCount++;

    printf("Freed PID: %d\n", pidmapIndex);
    return SUCCESSFUL;
}

// PID testing with Thread
void *pidAllocatorTest(void *param)
{
    int pid = allocate_pid();
    sleep(randomNumber(MIN_SLEEP_TIME, MAX_SLEEP_TIME));
    release_pid(pid);

    pthread_exit(0);
}

int randomNumber(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}