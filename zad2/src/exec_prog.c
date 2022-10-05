#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Potomny - UID: %u, GID: %u, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    return 0;
}
