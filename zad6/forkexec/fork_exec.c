#include <sem_lib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

sem_t *sem;

void onexit()
{
    sem_lib_close(sem);
    sem_lib_unlink(sem);
}

/* arg1 - nazwa programu */
/* arg2 - liczba procesów */
/* arg3 - liczba sekcji krytycznych każdego procesu */
int main(int argc, char *argv[])
{
    FILE *f;

    int ocz_war = atoi(argv[2]) * atoi(argv[3]);

    if(argc < 3)
    {
        printf("Bledna ilosc argumentow!\n");
        exit(-1);
    }

    sem = sem_lib_create();

    if(atexit(onexit) != 0)
    {
        printf("Blad przy wywolaniu funkcji atexit!\n");
        exit(-1);
    }

    // Utwórz plik i wpisz 0
    f = fopen("numer.txt", "w");
    fprintf(f, "%d", 0);
    fclose(f);

    int procAm = atoi(argv[2]);
    while(procAm > 0)
    {
        switch (fork())
        {
        case 0:
            execl(argv[1], argv[1], argv[3], NULL);
            perror("Nie udalo sie uruchomic programu z arg1!\n");
            break;
        
        default:
            break;
        }
        procAm--;
    }

    int stat_loc;
    while (wait(&stat_loc) != -1)
    {
        printf("Proces potomny zakonczyl prace. stat_loc: %d\n", stat_loc);
    }

    f = fopen("numer.txt", "r");
    int war;
    fscanf(f, "%d", &war);
    fclose(f);

    printf("Oczekiwana wartosc: %d. Otrzymana wartosc: %d\n", ocz_war, war);

    return 0;
}
