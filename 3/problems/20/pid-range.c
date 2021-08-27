#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MIN_PID 300
#define MAX_PID 5000

#define FAILED -1
#define SUCCESSFUL 1

#define FAILED_TO_CREATE_PID -1
#define FAILED_TO_KILL_PID -1

struct Pidmap
{
    char *map;
    int min;
    int max;
    int size;
    int current;
    int availableCount;
    char free;
    char occupied;
};

struct Pidmap pidmap;

int allocate_map();
int allocate_pid();
int release_pid(int pid);

struct Pidmap pidmap;

int main(void)
{
    if (allocate_map() == FAILED)
    {
        fprintf(stderr, "Failed to allocate pidmap");
        return -1;
    }

    for (int i = 0; i < 6000; i++)
    {
        int pid = allocate_pid();
        if (pid == FAILED)
        {
            fprintf(stderr, "Failed to create PID\n");
            return -1;
        }

        if (release_pid(pid) == FAILED)
        {
            fprintf(stderr, "Failed to release PID: %d", pid);
            return -1;
        }

        printf("PID: %d ", pid);
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
    return SUCCESSFUL;
}
