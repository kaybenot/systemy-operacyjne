#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

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
    for(i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case 0: /* proces potomny */
            setpgid(0, 0);
            print_ids(0);
            break;
        
        default: /* proces macierzysty */
            if(i == 0)
                print_ids(1);
            break;
        }
    }

    /* Czekanie na wykonanie wszystkich procesów */
    int stat_loc;
    while (wait(&stat_loc) != -1)
        printf("Funkcja wait zwrocila: %d\n", stat_loc);

    return 0;
}
