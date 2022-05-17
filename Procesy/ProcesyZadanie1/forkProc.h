#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "printIDs.h"

#ifndef FORKPROC
#define FORKPROC

void forkProc(int s)
{
    switch(fork()) // fork procesu
    {
        case -1: // funkcja fork() zwraca -1 jezeli blad
            perror("fork error");
            exit(1);
        case 0: // funkcja fork() zwraca 0 dla procesu potomnego
            printIDs(); // wypisanie identyfikatorow procesu potomnego
        default: // funkcja fork() zwraca PID procesu potomnego dla procesu macierzystego
            if(s > 0) // jezeli s>0 to uzywamy funkcji sleep() na s sekund
                sleep(s);
            else // w przeciwnym wypadku uzywamy wait()
                wait(NULL);

    }
}

#endif