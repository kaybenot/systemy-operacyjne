#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

typedef struct
{
    pthread_t tID;
    int nr;
}my_thread;

int licznik_wspolny = 0;

int thread_count = 0;
int thread_times = 0;

pthread_mutex_t mutex;
my_thread *IDs = NULL;

int run_threads = 0;

void gotoxy(unsigned x, unsigned y);
void *thread_func(void* data);

int main(int argc, char *argv[])
{
    /* Clear console */
    system("clear");

    if(argc < 3)
    {
        printf("Nieprawidlowa ilosc argumentow!\n");
        exit(-1);
    }
    thread_count = atoi(argv[1]);
    thread_times = atoi(argv[2]);

    /* Create mutex */
    if(pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("Error creating mutex!\n");
        exit(-1);
    }
    printf("Stworzono mutex w miejscu: %p.\n", (void*)&mutex);

    /* Create threads */
    IDs = (my_thread*)malloc(sizeof(my_thread) * thread_count);

    int i = 0;
    for(i = 0; i < thread_count; i++)
    {
        if(pthread_create(&IDs[i].tID, NULL, &thread_func, &IDs[i]) != 0)
        {
            printf("Error creating thread!\n");
            exit(-1);
        }
        IDs[i].nr = i;
        printf("Stworzono watek nr. %d.\n", i);
        sleep(1);
    }
    system("clear");
    run_threads = 1;

    printf("\033[0m");
    for(i = 0; i < thread_count; i++)
        pthread_join(IDs[i].tID, NULL);

    printf("Wszystkie watki zakonczyly swoja prace.\n");

    /* Sprawdzenie oczekiwanej wartosci */
    if((thread_times * thread_count) == licznik_wspolny)
        printf("Otrzymano oczekiwana wartosc %d.\n", licznik_wspolny);

    pthread_mutex_destroy(&mutex);
    return 0;
}

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH", y, x);
}

void *thread_func(void* data)
{
    my_thread *thread_data = data;
    int licznik_prywatny = 0;

    int i = 0;
    while(i < thread_times)
    {
        if(run_threads == 1)
        {
            /* Sekcja prywatna */
            gotoxy(0, thread_data->nr+1);
            printf("Sekcja prywatna nr %d watku: %d\n", i, thread_data->nr);
            sleep(1); /* Opoznienie po sekcji prywatnej */

            /* Sekcja krytyczna */
            pthread_mutex_lock(&mutex);

            gotoxy(0, thread_data->nr+1);
            printf("                                       \n");

            licznik_prywatny = licznik_wspolny;
            gotoxy(40, 1);
            printf("Sekcja krytyczna przez watek nr %d\n", thread_data->nr);
            gotoxy(40, 2);
            printf("Odczytal %d zapisze %d\n", licznik_prywatny, licznik_prywatny + 1);
            licznik_prywatny++;
            sleep(2);
            licznik_wspolny = licznik_prywatny;
            pthread_mutex_unlock(&mutex);

            i++;
        }
    }
    return 0;
}
