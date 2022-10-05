#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int sig)
{
    printf("Przechwycono i obslozono sygnal.\n");
}

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        signal(atoi(argv[1]), sig_handler);
    }
    else if(argc == 3)
    {
        if(strcmp("default", argv[2]) == 0)
        {
            if(signal(atoi(argv[1]), SIG_DFL) == SIG_ERR)
            {
                perror("Nie udalo ustawic sie funkcji domyslnej dla sygnalu.");
                exit(-1);
            }
        }
        else if(strcmp("ignore", argv[2]) == 0)
        {
            if(signal(atoi(argv[1]), SIG_IGN) == SIG_ERR)
            {
                perror("Nie udalo ustawic sie funkcji ignorowania dla sygnalu.");
                exit(-1);
            }
        }
    }
    while(1)
        pause();

    return 0;
}
