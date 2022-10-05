#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char *fifo;

void exit_func()
{
    unlink(fifo);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Nieprawidlowa ilosc argumentow.\nPodaj nazwe pliku fifo!\n");
        exit(EXIT_FAILURE);
    }

    if(mkfifo(argv[1], 0777) == -1)
    {
        printf("Nie udalo sie utworzyc pliku przez mkfifo!\n");
        exit(EXIT_FAILURE);
    }
    fifo = argv[1];

    if(atexit(exit_func))
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    int stat_loc;
    switch (fork())
    {
    case 0: /* Potomny */
        execl("pro_kons", "pro_kons", argv[1], NULL);
        break;
    
    default:
        while (wait(&stat_loc) != -1)
            printf("Proces potomny zwrocil %d\n", stat_loc);
        break;
    }

    return 0;
}