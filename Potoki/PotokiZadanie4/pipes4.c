//############################################//
//                                            //
//    Jan Kwinta                05.04.2022    //
//                                            //
//                                            //
//    Projekt: Potoki Zadanie 4               //
//    Plik: pipes4.c                          //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* funkcja sprawdzajaca poprawnosc argumentow uruchomienia */
void argCheck(int argc, char **argv)
{
    /* sprawdzenie czy ilosc argumentow jest poprawna */
    if(argc != 3)
    {
        printf("ERROR\nNiepoprawna liczba argumentow\nPatrz README\n");
        exit(101);
    }

    /* sprawdzenie czy nazwa pliku wejscia nie jest identyczna z nazwa pliku wyjscia */
    if(strcmp(argv[1], argv[2]) == 0)
    {
        printf("ERROR\nNiepoprawne argumenty\nPatrz README\n");
        exit(102);
    }
}


int main(int argc, char **argv)
{
    /* sprawdzenie argumentow */
    argCheck(argc, argv);

    /* utowrzenie potoku nienazwanego */
    int pipeFileDesc[2];
    if(pipe(pipeFileDesc) == -1)
    {
        perror("creating pipe error");
        exit(201);
    }

    /* stworzenie zmiennych tekstowych, aby podac dekryptory 
       potoku do podprogramow */
    char fileDescRead[10];
    if(sprintf(fileDescRead, "%d", pipeFileDesc[0]) < 0)
    {
        perror("sprintf error");
        exit(301);
    }

    char fileDescWrite[10];
    if(sprintf(fileDescWrite, "%d", pipeFileDesc[1]) < 0)
    {
        perror("sprintf error");
        exit(302);
    }

    /* fork procesu - proces potomny wykonywac bedzie program
       producenta, a proces macierzysty program konsumenta */
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            if(execlp("./progProducer.x", "./progProducer.x", argv[1], fileDescRead, fileDescWrite, NULL) == -1)
            {
                perror("execlp error");
                _exit(501);
            } 
        default:
            sleep(2);
            if(execlp("./progConsumer.x", "./progConsumer.x", argv[2], fileDescRead, fileDescWrite, NULL) == -1)
            {
                perror("execlp error");
                _exit(502);
            }
    }
    
    return 0;
}