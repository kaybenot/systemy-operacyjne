#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <math.h>

void print_ids(int pid)
{
    if(pid == 0)
        printf("Potomny - UID: %u, GID: %u, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    else
        printf("Macierzysty - UID: %u, GID: %u, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
}

int main()
{
    int i;
    int potomny = 0;
    for(i = 0; i < 3; i++)
    {
        int pid = fork();
        if(pid == 0) /* proces potomny */
        {
            potomny = 1;
            print_ids(0);
            sleep(4 + i);
        }
        else /* proces macierzysty */
        {
            sleep(1);
        }
    }

    if(potomny == 0)
    {
        sleep(10);
        print_ids(1);
    }
    sleep(5);

    return 0;
}
