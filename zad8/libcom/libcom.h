#pragma once
#include <mqueue.h>

#define MAX_MSG 5
#define MAX_SIZE 64

mqd_t com_create(const char *name);

mqd_t com_open(const char *name);

void com_close(mqd_t des);

void com_unlink(const char *name);

void com_send(char *msg, mqd_t des);

void com_receive(mqd_t des, char *buff);
