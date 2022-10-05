#define _REENTRANT
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WATKI 3
#define SEKCJE 3

void *alg(void *data);
bool para_wieksza(int a1, int a2, int b1, int b2);
void gotoxy(unsigned x, unsigned y);

typedef struct
{
    pthread_t tID;
    int nr;
}my_thread;

my_thread IDs[WATKI];
bool start_threads = false;

bool wybieranie[WATKI];
int numer[WATKI];

int licznik_wspolny = 0;

int i;

int main(int argc, char *argv[])
{
    for(i = 0; i < WATKI; i++)
    {
        wybieranie[i] = false;
        numer[i] = 0;
        if(pthread_create(&IDs[i].tID, NULL, &alg, &IDs[i]) != 0)
        {
            perror("Blad przy tworzeniu watku.");
            exit(-1);
        }
        IDs[i].nr = i;
        printf("Stworzono watek nr. %d.\n", i);
        sleep(1);
    }
    system("clear");
    start_threads = true;

    for(i = 0; i < WATKI; i++)
        pthread_join(IDs[i].tID, NULL);

    printf("\033[0m");
    printf("Wszystkie watki zakonczyly swoja prace.\n");

    printf("Oczekiwana wartość: %d, otrzymana wartość %d.\n", WATKI * SEKCJE, licznik_wspolny);

    return 0;
}

void *alg(void *data)
{
    my_thread *thread = data;
    int wykonane_sekcje = 0;
    int licznik_prywatny = 0;
    int j;
    while(wykonane_sekcje < SEKCJE)
    {
        if(start_threads)
        {
            /* Sekcja prywatna start */

            printf("\033[%d;1HSekcja prywatna nr %d watku: %d\n", thread->nr + 1, wykonane_sekcje, thread->nr);

            /* Sekcja prywatna koniec */

            wybieranie[thread->nr] = true;
            int max = 0;
            for(j = 0; j < WATKI; j++)
            {
                if(max < numer[j])
                    max = numer[j];
            }
            numer[thread->nr] = max + 1;
            wybieranie[thread->nr] = false;

            for(j = 0; j < WATKI; j++)
            {
                while(wybieranie[j]);
                while((numer[j] != 0) && para_wieksza(numer[j], j, numer[thread->nr], thread->nr));
            }
            /* Sekcja krytyczna start */

            printf("\033[%d;%dH\033[2K", thread->nr+1, 0);

            licznik_prywatny = licznik_wspolny;
            printf("\033[1;40HSekcja krytyczna przez watek nr %d\n", thread->nr);
            printf("\033[2;40HOdczytal %d zapisze %d\n", licznik_prywatny, licznik_prywatny + 1);
            licznik_prywatny++;
            sleep(2);
            licznik_wspolny = licznik_prywatny;
            numer[thread->nr] = 0;

            /* Sekcja krytyczna koniec */
            wykonane_sekcje++;
        }
    }
    return 0;
}

bool para_wieksza(int a1, int a2, int b1, int b2)
{
    if(a1 < b1)
        return true;
    else if((a1 == b1) && (a2 < b2))
        return true;
    else
        return false;
}

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH", y, x);
}
