#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "argErrors.h"

int main(int argc, char **argv)
{
    if(argErrors(argc, argv) != 0)
        exit(1);

    int signalNumber = atoi(argv[2]);

    pid_t childPID;
    switch(childPID = fork()) // fork procesu
    {
        case -1: // blad
            perror("fork error");
            exit(2);
        case 0: // dla procesu potomnego
            if(execlp("./signalsA.x", "./signalsA.x", argv[1], argv[2], NULL) == -1)
            {
                perror("execlp error");
                exit(3);
            }
        default: // dla procesu macierzystego
            sleep(1);
            if(kill(childPID, 0) == -1)
            {
                perror("proces potomny nie istnieje");
                exit(4);
            }
            if(kill(childPID, signalNumber) == -1)
            {
                perror("kill error");
                exit(5);
            }
    }

    return 0;
}
