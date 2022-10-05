#include "libcom.h"
#include <unistd.h>
#include <stdio.h>
#include <memory.h>

int main(int argc, char *argv[])
{
    int PID = getpid();
    char str[12];
    str[0] = '/';

    /* Convert PID to char array */
    sprintf(&str[1], "%d", PID);

    mqd_t recvq = com_create(str);
    mqd_t serverq = com_open("/server_queue");

    char buff[MAX_SIZE];
    char recv[MAX_SIZE];
    int n = sprintf(buff, "%d ", PID);
    while(fgets(&buff[n], MAX_SIZE - n, stdin) != NULL)
    {
        com_send(buff, serverq);
        printf("Wyslano dzialanie %s", buff + n);
        com_receive(recvq, recv);
        printf("Otrzymano wynik: %s\n", recv);
    }

    com_close(serverq);
    com_close(recvq);
    com_unlink(str);

    return 0;
}
