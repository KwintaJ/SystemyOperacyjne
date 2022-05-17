#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "argErrors.h"

/* funkcja do wlasnej obslugi otrzymanego sygnalu */
void handler(int v)
{
    printf("\nsignalsA: Proces %d: Wlasna obsluga sygnalu numer %d\n", getpid(), v);
}

int main(int argc, char **argv)
{
    if(argErrors(argc, argv) != 0) // sprawdzenie poprawnosci argumentow
        exit(1);

    int signalNumber = atoi(argv[2]); // numer sygnalu ktory ma obslugiwac program

    switch(argv[1][0]) // wybor zadanej opcji
    {
        case 'd': // domyslna
            if(signal(signalNumber, SIG_DFL) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            pause();

        case 'i': // ignorowanie
            if(signal(signalNumber, SIG_IGN) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            pause();

        case 'h': // przechwycenie i obsluga wlasna
            if(signal(signalNumber, handler) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            pause();
    }

    return 0;
}