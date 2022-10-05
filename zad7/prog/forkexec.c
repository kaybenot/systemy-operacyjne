#include "libseg.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int seg_des;
segment_pd *seg;
sem_t *sem_kons;
sem_t *sem_prod;

void onexit()
{
    sem_lib_close(sem_kons);
    sem_lib_close(sem_prod);
    sem_lib_unlink("sem_konsument");
    sem_lib_unlink("sem_producent");
    seg_close(seg, seg_des);
    seg_unlink();
}

int main(int argc, char *argv[])
{
    seg = seg_create(&seg_des);

    sem_kons = sem_lib_create("sem_konsument", 0);
    sem_prod = sem_lib_create("sem_producent", NBUF);

    if(atexit(onexit) != 0)
    {
        printf("Nie udalo sie zarejestrowac funkcji atexit!\n");
        exit(-1);
    }

    int prod = open("produkty.txt", O_CREAT | O_TRUNC, 0777);
    close(prod);

    switch (fork())
    {
    case 0:
        execl("producent", "producent", NULL);
        perror("Nie udalo sie uruchomic procesu producenta!");
        break;
    
    default:
        break;
    }

    switch (fork())
    {
    case 0:
        execl("konsument", "konsument", NULL);
        perror("Nie udalo sie uruchomic procesu konsumenta!");
        break;
    
    default:
        break;
    }

    int stat_loc;
    while (wait(&stat_loc) != -1)
        printf("Proces potomny zakonczyl sie. stat_loc: %d\n", stat_loc);
    
    return 0;
}