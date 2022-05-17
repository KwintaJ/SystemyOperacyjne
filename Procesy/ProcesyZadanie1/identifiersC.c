#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "printIDs.h"
#include "forkProc.h"

int main()
{
    printf("Proces macierzysty:\n");
    printIDs(); // wypisanie identyfikatorow procesu-matki
    printf("Procesy potomne:\n");
    for(int i = 0; i < 3; i++)
        forkProc(3); // stworzenie procesu potomnego 
                     // argument 3 oznacza ze funkcja forkProc
                     // uzyje funkcji sleep(3)
    return 0;
}