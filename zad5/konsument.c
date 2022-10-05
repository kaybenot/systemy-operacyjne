#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int potok_naz = open(argv[1], O_RDWR, 0777);

    int prod = open("produkty.txt", O_WRONLY | O_CREAT, 0777);

    char buff;
    while(read(potok_naz, &buff, 1) != 0)
    {
        write(prod, &buff, 1);
        printf("Otrzymano produkt: %c\n", buff);
    }

    return 0;
}