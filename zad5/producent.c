#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int potok_naz = open(argv[1], O_RDWR, 0777);

    int sur = open("surowce.txt", O_RDONLY, 0777);

    char buff;
    while(read(sur, &buff, 1) != 0)
    {
        printf("Przetwarzanie: %c\n", buff);
        sleep(rand() % 4);
        write(potok_naz, &buff, 1);
        printf("Przetworzono: %c\n", buff);
    }

    return 0;
}