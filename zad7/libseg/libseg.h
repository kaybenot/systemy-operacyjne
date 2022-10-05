#define NELE 20
#define NBUF 5

#include <semaphore.h>

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
}segment_pd;

sem_t *sem_lib_create(const char* arr, int val);

sem_t *sem_lib_open(const char* arr);

void sem_lib_close(sem_t *sem);

void sem_lib_unlink(const char* name);

void sem_lib_wait(sem_t *sem);

void sem_lib_post(sem_t *sem);

int sem_lib_getval(sem_t *sem);

segment_pd *seg_create(int *seg_des_r);

segment_pd *seg_open(int *seg_des_r);

void seg_close(segment_pd *seg, int seg_des);

void seg_unlink();

char *seg_wyjmij(segment_pd *seg);

void seg_wstaw(char *data, segment_pd *seg);