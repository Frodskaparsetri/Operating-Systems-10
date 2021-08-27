#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    // https://stackoverflow.com/a/25228579
    /* 
        Two methods of checking:
        1. open two terminals
            - terminal 1: write ./zombie
            - terminal 2: write ps -l
            - terminal 2: observe Zombie Process (Z+, ZN, Z)
        2. write in terminal ./zombie &
            - (this will run it concurrently)
            - write: ps -l
            - observe Zombie Process (Z+, ZN, Z)
    */

    pid_t pid = fork();
    if (pid == 0)
    {
        return 0;
    }

    printf("Zombie Child Process Created\n PID: %d\n Alive for 10 seconds...", pid);
    sleep(10);
    return 0;
}