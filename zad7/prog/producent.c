#include "libseg.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    sem_t *sem_kons;
    sem_t *sem_prod;

    segment_pd *seg;
    int seg_des;

    sem_prod = sem_lib_open("sem_producent");
    sem_kons = sem_lib_open("sem_konsument");

    seg = seg_open(&seg_des);

    int sur = open("surowce.txt", O_RDONLY, 0777);
    char buf[NELE + 1];
    buf[NELE] = '\0';

    int b_read;
    while ((b_read = read(sur, &buf, NELE)) != 0)
    {
        if(b_read < NELE)
            buf[b_read] = '\0';
        sem_lib_wait(sem_prod);
        seg_wstaw(buf, seg);
        printf("Przetworzono: %s\n", buf);
        sem_lib_post(sem_kons);
    }
    buf[0] = '\0';
    sem_lib_wait(sem_prod);
    seg_wstaw(buf, seg);
    sem_lib_post(sem_kons);
    
    sem_lib_close(sem_kons);
    sem_lib_close(sem_prod);

    seg_close(seg, seg_des);
    close(sur);
    return 0;
}
