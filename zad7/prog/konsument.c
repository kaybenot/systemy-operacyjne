#include "libseg.h"
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    segment_pd *seg;
    int seg_des;

    sem_t *sem_kons;
    sem_t *sem_prod;

    seg = seg_open(&seg_des);

    sem_prod = sem_lib_open("sem_producent");
    sem_kons = sem_lib_open("sem_konsument");

    char buf[NELE + 1];
    buf[NELE] = '\0';

    int prod;
    while(1)
    {
        sem_lib_wait(sem_kons);
        char *got = seg_wyjmij(seg);
        if(got != NULL)
        {
            if(got[0] == '\0')
            {
                sem_lib_post(sem_prod);
                break;
            }
            memcpy(buf, got, NELE);
            
            prod = open("produkty.txt", O_WRONLY | O_APPEND, 0777);
            write(prod, buf, strlen(buf));
            close(prod);

            printf("Otrzymano produkt: %s\n", buf);
        }
        sem_lib_post(sem_prod);
    }

    sem_lib_close(sem_kons);
    sem_lib_close(sem_prod);

    seg_close(seg, seg_des);
    return 0;
}