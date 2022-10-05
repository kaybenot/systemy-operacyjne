#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Nieprawidlowa ilosc argumentow.\nWpisz nazwe programu do uruchomienia.\n");
        return -1;
    }
    int i;
    for(i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case 0: /* proces potomny */
            execl(argv[1], argv[1], (char*)NULL);
            printf("Nie udalo sie uruchomic programu procesu potomnego!\n");
            break;
        
        default: /* proces macierzysty */
            if(i == 0)
                printf("Macierzysty - UID: %u, GID: %u, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
            break;
        }
    }

    /* Czekanie na wykonanie wszystkich procesów */
    int stat_loc;
    while (wait(&stat_loc) != -1)
        printf("Funkcja wait zwrocila: %d\n", stat_loc);

    return 0;
}
