#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    int potomny;
    switch (potomny = fork())
    {
    case 0:
    {
        if(argc == 2)
            execl("sig_a", "sig_a", argv[1], (char*)NULL);
        else if(argc == 3)
            execl("sig_a", "sig_a", argv[1], argv[2], (char*)NULL);
        printf("Nie udalo sie uruchomic programu procesu potomnego!\n");
        break;
    }
    default:
    {
        kill(potomny, 0);
        if(errno == ESRCH)
        {
            printf("Proces potomny nie istnieje");
            return -1;
        }
        sleep(2);
        kill(potomny, atoi(argv[1]));
        int stat_loc;
        int pid = wait(&stat_loc);
        stat_loc = stat_loc & 0xFF;
        printf("Proces o PID: %d zwrocil wartosc: %d\n", pid, stat_loc);
        break;
    }
    }

    return 0;
}
