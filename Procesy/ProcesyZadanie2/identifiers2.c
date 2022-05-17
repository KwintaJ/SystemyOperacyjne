#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "printIDs.h"

int main()
{
    printf("Proces macierzysty:\n");
    printIDs(); // wypisanie identyfikatorow procesu-matki
    printf("Procesy potomne:\n");
    for(int i = 0; i < 3; i++)
        switch(fork()) // fork procesu
        {
            case -1: // funkcja fork() zwraca -1 jezeli blad
                perror("fork error");
                exit(1);
            case 0:
                /* wywolanie w konsoli zewnetrznego programu do wypisywania
                   idenytfikatorow procesow potomnych                       */
                execlp("./extPrint.x", "./extPrint.x", (char *)NULL); 
            default:
                wait(NULL); // proces macierzysty czeka na zakonczenie sie potomka

        }
    return 0;
}