#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Identyfikatory obecnego procesu:\n");
    printf("UID: %u\n", getuid());
    printf("GID: %u\n", getgid());
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgrp());
    return 0;
}
