#include "libcom.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

mqd_t com_create(const char *name)
{
    struct mq_attr atr = {0, MAX_MSG, MAX_SIZE, 0};

    mqd_t des = mq_open(name, O_CREAT | O_RDWR | O_EXCL, 0644, &atr);
    if(des == (mqd_t)(-1))
    {
        perror("Nie udalo sie utworzyc komunikatu!\n");
        exit(-1);
    }
    return des;
}

mqd_t com_open(const char *name)
{
    mqd_t des = mq_open(name, O_WRONLY);
    if(des == (mqd_t)(-1))
    {
        perror("Nie udalo sie otworzyc komunikatu!\n");
        exit(-1);
    }
    return des;
}

void com_close(mqd_t des)
{
    if(mq_close(des) == -1)
        perror("Nie udalo sie zamknac komunikatu!\n");
}

void com_unlink(const char *name)
{
    if(mq_unlink(name) == -1)
        perror("Nie udalo sie usunac komunikatu!\n");
}

void com_send(char *msg, mqd_t des)
{
    if(mq_send(des, msg, MAX_SIZE, 0) == -1)
        perror("Nie udalo sie wyslac komunikatu!\n");
}

void com_receive(mqd_t des, char *buff)
{
    if(mq_receive(des, buff, MAX_SIZE, NULL) == -1)
        perror("Nie udalo sie otrzymac komunikatu!\n");
}
