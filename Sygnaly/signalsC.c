#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "argErrors.h"

/* liczba procesow potomnych drugiego pokolenia 
   (w tresci zadania: kilka) */
const int PROCNUM = 3;

int main(int argc, char **argv)
{
    if(argErrors(argc, argv) != 0)
        exit(1);

    int signalNumber = atoi(argv[2]);
    pid_t childPID, childPGID;

    switch(childPID = fork()) // fork procesu
    {
        case -1: // blad
            perror("fork error");
            exit(2);

        case 0: // dla procesu potomnego
            setpgid(0, 0); // ustawienie procesu potomego 
                           // pierwszego pokolenia jako lidera grupy
            printf("\nsignalsC: Pierwszy proces potomny PID=%d; PGID=%d.\n", getpid(), getpgrp());

            /* proces potomny pierwszego pokolenia ignoruje sygnaly wysylane
               przez proces macierzysty */
            if(signal(signalNumber, SIG_IGN) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }

            for(int i = 0; i < PROCNUM; i++)
            {
                pid_t chProc;
                switch(fork()) // fork procesu
                {

                    case -1: // blad
                        perror("fork error");
                        exit(2);
                    case 0: // dla procesu potomnego drugiego pokolenia
                        if(execlp("./signalsA.x", "./signalsA.x", argv[1], argv[2], NULL) == -1)
                        {
                            perror("execlp error");
                            exit(3);
                        }
                    default: // dla proc. potomnego pierwszego pokolenia
                        chProc =  wait(NULL);
                        if(chProc == -1)
                        {
                            perror("wait error");
                            exit(4);
                        }
                        printf("\nsignalsC: Proces potomny o PID=%d zostal zakonczony.\n", chProc);
                }
            }

            printf("\nsignalsC: Wszystkie procesy potomne zakonczyly sie.\n");


        default: // dla procesu macierzystego
            sleep(1);
            /* PGID procesu potomnego pierwszrgo pokolenia */
            if((childPGID = getpgid(childPID)) == -1)
            {
                perror("getpgid error");
                exit(5);
            }
            for(int i = 0; i < PROCNUM; i++)
            {
                sleep(1);
                /* sprawdzanie czy grupa procesow o PGID = childPGID istnieje */
                if(kill(childPGID * (-1), 0) == -1)
                {
                    perror("grupa procesow potomnych nie istnieje");
                    exit(6);
                }
                /* wysylanie sygnalu do grupy procesow o PGID = childPGID */
                if(kill(childPGID * (-1), signalNumber) == -1)
                {
                    perror("kill error");
                    exit(7);
                }
            }
    }

    return 0;
}
