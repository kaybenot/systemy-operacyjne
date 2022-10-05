#include <sem_lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* arg1 - liczba sekcji krytycznych */
int main(int argc, char *argv[])
{
    FILE *f;
    sem_t *sem;
    sem = sem_lib_open();

    int i = atoi(argv[1]);
    while (i > 0)
    {
        printf("[%d]Przed sekcja krytyczna. Wartość semafora: %d\n", getpid(), sem_lib_getval(sem));
        
        /* Sekcja krytyczna */
        sem_lib_wait(sem);
        printf("    [%d] W trakcie sekcji krytycznej. Wartość semafora: %d\n", getpid(), sem_lib_getval(sem));

        /* Przetwarzanie 1s */
        sleep(1);
        

        /* Read val */
        f = fopen("numer.txt", "r");
        int val;
        fscanf(f, "%d", &val);
        fclose(f);

        /* Print val + 1 */
        val++;
        f = fopen("numer.txt", "w");
        fprintf(f, "%d", val);
        fclose(f);

        sem_lib_post(sem);
        /* Koniec sekcji krytycznej */
        
        printf("[%d]Po sekcji krytycznej. Wartość semafora: %d\n", getpid(), sem_lib_getval(sem));
        i--;
    }
    

    sem_lib_close(sem);
    return 0;
}
