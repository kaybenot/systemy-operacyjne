#pragma once
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

sem_t *sem_lib_create();

sem_t *sem_lib_open();

void sem_lib_close(sem_t *semf);

void sem_lib_unlink();

void sem_lib_wait(sem_t *semf);

void sem_lib_post(sem_t *semf);

int sem_lib_getval(sem_t *semf);
