#include "libcom.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <signal.h>

const char delim[2] = " ";

int calc(int n1, int n2, char sign);
void onexit();
void signal_capture();

mqd_t recvq;

int main(int argc, char *argv[])
{
    if(atexit(onexit) != 0)
        perror("Could not set atexit");

    if(signal(SIGINT, signal_capture))
        perror("Could not set signal capturing");

    recvq = com_create("/server_queue");

    char recv[MAX_SIZE];
    while (1)
    {
        com_receive(recvq, recv);
        int PID;
        int n1;
        int n2;
        char sign;

        char *token = strtok(recv, delim);
        int i = 0;
        while (token != NULL)
        {
            switch (i)
            {
            case 0: /* PID */
                sscanf(token, "%d", &PID);
                token = strtok(NULL, delim);
                i++;
                continue;
            case 1: /* 1st number */
                sscanf(token, "%d", &n1);
                token = strtok(NULL, delim);
                i++;
                continue;
            case 2: /* sign */
                sscanf(token, "%c", &sign);
                token = strtok(NULL, delim);
                i++;
                continue;
            case 3: /* 2nd number */
                sscanf(token, "%d", &n2);
                i++;
                continue;
            
            default:
                break;
            }
            break;
        }
        printf("Otrzymano dzialanie od PID: %d o tresci: %d %c %d.\n", PID, n1, sign, n2);

        char str[12];
        sprintf(str, "/%d", PID);
        mqd_t sendq = com_open(str);
        char msg[MAX_SIZE];
        int wyn = calc(n1, n2, sign);
        sprintf(msg, "%d ", wyn);
        com_send(msg, sendq);
        printf("Wyslano wynik: %d do PID: %d\n", wyn, PID);
        com_close(sendq);
    }

    return 0;
}

int calc(int n1, int n2, char sign)
{
    switch (sign)
    {
    case '+':
        return n1 + n2;
    case '-':
        return n1 - n2;
    case '*':
        return n1 * n2;
    case '/':
        return n1 / n2;
    
    default:
        return 0;
    }
}

void onexit()
{
    com_close(recvq);
    com_unlink("/server_queue");
}

void signal_capture()
{
    exit(0);
}
