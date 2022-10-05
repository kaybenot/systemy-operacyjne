#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int potok_naz;

void producent()
{
    int sur = open("surowce.txt", O_RDONLY, 0777);

    char buff;
    while(read(sur, &buff, 1) != 0)
    {
        printf("Przetwarzanie: %c\n", buff);
        sleep(rand() % 4);
        write(potok_naz, &buff, 1);
        printf("Przetworzono: %c\n", buff);
    }

}

void konsument()
{
    int prod = open("produkty.txt", O_WRONLY | O_CREAT, 0777);

    char buff;
    while(read(potok_naz, &buff, 1) != 0)
    {
        write(prod, &buff, 1);
        printf("Otrzymano produkt: %c\n", buff);
    }
}

int main(int argc, char *argv[])
{
    srand(0);

    potok_naz = open(argv[1], O_RDWR, 0777);

    switch (fork())
    {
    case 0:
        konsument();
        break;
    
    default:
        producent();
        break;
    }

    return 0;
}