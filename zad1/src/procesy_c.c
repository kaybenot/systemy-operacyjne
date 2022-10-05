#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    for(i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case 0: /* proces potomny */
            sleep(30);
            break;
        
        default: /* proces macierzysty */
            break;
        }
    }

    return 0;
}
