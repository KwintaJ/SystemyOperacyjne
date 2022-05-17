#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "printIDs.h"

int main()
{
    printIDs();
    for(int i = 0; i < 3; i++)
    {
        sleep(1);
        switch(fork()) // fork procesu
        {
            case -1: // funkcja fork() zwraca -1 jezeli blad
                perror("fork error");
                exit(1);
            case 0: // funkcja fork() zwraca 0 dla procesu potomnego
                printIDs(); // wypisanie identyfikatorow procesu potomnego
            default: // funkcja fork() zwraca PID procesu potomnego dla procesu macierzystego
                sleep(5-i); // proces macierzysty czeka najdluzej
                            // zeby wszystkie procesy potomne sie zakonczyly wczesniej
        }
    }
    return 0;
}