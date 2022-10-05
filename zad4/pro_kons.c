#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int filedes[2];

void producent()
{
    int sur = open("surowce.txt", O_RDONLY, 0b111111111);

    char buff;
    while(read(sur, &buff, 1) != 0)
    {
        printf("Przetwarzanie: %c\n", buff);
        sleep(rand() % 4);
        write(filedes[1], &buff, 1);
        printf("Przetworzono: %c\n", buff);
    }

}

void konsument()
{
    int prod = open("produkty.txt", O_WRONLY | O_CREAT, 0b111111111);

    char buff;
    while(read(filedes[0], &buff, 1) != 0)
    {
        write(prod, &buff, 1);
        printf("Otrzymano produkt: %c\n", buff);
    }
}

int main()
{
    srand(0);

    pipe(filedes);

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
