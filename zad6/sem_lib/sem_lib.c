#include "sem_lib.h"
#include <stdio.h>
#include <stdlib.h>

sem_t *sem_lib_create()
{
    sem_t* sem = sem_open("semafor", O_CREAT | O_EXCL, 0777, 1);
    if(sem == SEM_FAILED)
    {
        printf("Error creating semaphore!\n");
        exit(-1);
    }
    return sem;
}

sem_t *sem_lib_open()
{
    sem_t* sem = sem_open("semafor", 0);
    if(sem == SEM_FAILED)
    {
        printf("Error opening semaphore!\n");
        exit(-1);
    }
    return sem;
}

void sem_lib_close(sem_t *semf)
{
    if(sem_close(semf) == -1)
    {
        printf("Error closing semaphore!\n");
        exit(-1);
    }
}

void sem_lib_unlink()
{
    if(sem_unlink("semafor") == -1)
    {
        printf("Error removing semaphore!\n");
        exit(-1);
    }
}

void sem_lib_wait(sem_t *semf)
{
    if(sem_wait(semf) == -1)
    {
        printf("Error sem_wait!\n");
        exit(-1);
    }
}

void sem_lib_post(sem_t *semf)
{
    if(sem_post(semf) == -1)
    {
        printf("Error sem_post!\n");
        exit(-1);
    }
}

int sem_lib_getval(sem_t *semf)
{
    int val = 0;
    if(sem_getvalue(semf, &val) == -1)
    {
        printf("Error sem_getvalue!\n");
        exit(-1);
    }
    return val;
}
