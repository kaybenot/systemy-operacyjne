#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    int potomny;
    int stat_loc;
    int i;
    int group;
    switch (potomny = fork())
    {
    case 0:
    {
        setpgid(0, 0);
        group = getpgrp();
        for(i = 0; i < 3; i++)
        {
            switch (fork())
            {
            case 0:
            {
                setpgid(0, group);
                if(argc == 2)
                    execl("sig_a", "sig_a", argv[1], (char*)NULL);
                else if(argc == 3)
                    execl("sig_a", "sig_a", argv[1], argv[2], (char*)NULL);
                printf("Nie udalo sie uruchomic programu procesu potomnego!\n");
                break;
            }
            default:
                break;
            }
        }
        sleep(2);
        kill(0, atoi(argv[1]));
        while (wait(&stat_loc) != -1)
            printf("Proces potomny zwrocil: %d\n", stat_loc & 0xFF);
        break;
    }
    default:
        while (wait(&stat_loc) != -1)
            printf("Proces potomny zwrocil: %d\n", stat_loc & 0xFF);
        break;
    }

    return 0;
}
