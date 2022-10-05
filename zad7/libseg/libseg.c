#include "libseg.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>

sem_t *sem_lib_create(const char* name, int val)
{
    sem_t *sem;
    sem = sem_open(name, O_CREAT, 0777, val);
    if(sem == SEM_FAILED)
    {
        printf("Error creating semaphore!\n");
        exit(-1);
    }
    return sem;
}

sem_t *sem_lib_open(const char* name)
{
    sem_t *sem;
    sem = sem_open(name, 0);
    if(sem == SEM_FAILED)
    {
        printf("Error opening semaphore!\n");
        exit(-1);
    }
    return sem;
}

void sem_lib_close(sem_t *sem)
{
    if(sem_close(sem) == -1)
    {
        printf("Error closing semaphore!\n");
        exit(-1);
    }
}

void sem_lib_unlink(const char* name)
{
    if(sem_unlink(name) == -1)
    {
        printf("Error removing semaphore!\n");
        exit(-1);
    }
}

void sem_lib_wait(sem_t *sem)
{
    if(sem_wait(sem) == -1)
    {
        printf("Error sem_wait!\n");
        exit(-1);
    }
}

void sem_lib_post(sem_t *sem)
{
    if(sem_post(sem) == -1)
    {
        printf("Error sem_post!\n");
        exit(-1);
    }
}

int sem_lib_getval(sem_t *sem)
{
    int val = 0;
    if(sem_getvalue(sem, &val) == -1)
    {
        printf("Error sem_getvalue!\n");
        exit(-1);
    }
    return val;
}

segment_pd *seg_create(int *seg_des_r)
{
    segment_pd *seg;
    int seg_des;
    seg_des = shm_open("PAM_DZIEL", O_RDWR | O_CREAT, 0777);
    if(seg_des == -1)
    {
        printf("Nie udalo sie utworzyc pamieci dzielonej!\n");
        exit(-1);
    }

    if(ftruncate(seg_des, sizeof(segment_pd)) == -1)
    {
        printf("Nie udalo sie rozszerzyc pamieci dzielonej!\n");
        exit(-1);
    }

    seg = (segment_pd*)mmap(NULL, sizeof(segment_pd), PROT_READ | PROT_WRITE, MAP_SHARED, seg_des, 0);
    if(seg == MAP_FAILED)
    {
        printf("Nie udalo sie przypisac pamieci dzielonej do przestrzeni adresowej!\n");
        exit(-1);
    }
    seg->wstaw = 0;
    seg->wyjmij = 0;

    *seg_des_r = seg_des;
    return seg;
}

segment_pd *seg_open(int *seg_des_r)
{
    segment_pd *seg;
    int seg_des;
    seg_des = shm_open("PAM_DZIEL", O_RDWR, 0777);
    if(seg_des == -1)
    {
        printf("Nie udalo sie otworzyc pamieci dzielonej!\n");
        exit(-1);
    }

    seg = (segment_pd*)mmap(NULL, sizeof(segment_pd), PROT_READ | PROT_WRITE, MAP_SHARED, seg_des, 0);
    if(seg == MAP_FAILED)
    {
        printf("Nie udalo sie przypisac pamieci dzielonej do przestrzeni adresowej!\n");
        exit(-1);
    }

    *seg_des_r = seg_des;
    return seg;
}

void seg_close(segment_pd *seg, int seg_des)
{
    if(munmap(seg, sizeof(segment_pd)) == -1)
    {
        printf("Nie udalo sie zamknac pamieci dzielonej od przestrzeni adresowej!\n");
    }

    if(close(seg_des) == -1)
        printf("Nie udalo sie zamknac pamieci dzielonej!\n");

}

void seg_unlink()
{
    if(shm_unlink("PAM_DZIEL") == -1)
        printf("Nie udalo sie usunac pamieci dzielonej!\n");
}

char *seg_wyjmij(segment_pd *seg)
{
    char *data = seg->bufor[seg->wyjmij];
    
    /* Rotacja */
    seg->wyjmij = (seg->wyjmij + 1) % NBUF; 
    
    return data;
}

void seg_wstaw(char *data, segment_pd *seg)
{
    memcpy(seg->bufor[seg->wstaw], data, NELE);

    /* Rotacja */
    seg->wstaw = (seg->wstaw + 1) % NBUF; 
}
