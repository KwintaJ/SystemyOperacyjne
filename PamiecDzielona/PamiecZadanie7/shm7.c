//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: shm7.c                            //
//                                            //
//    Program glowny                          //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "semaph_lib.h"
#include "memory_lib.h"

const char *semaphName = "prod-cons-semaphor";

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

/* funkcja wywolywana na koncu programu */
void removeEverything()
{
    delete_semaph(semaphName);
}

int main(int argc, char **argv)
{
    /* sprawdzenie argumentow */
    argCheck(argc, argv);

    /* utworzenie semafora */
    sem_t *semaphAdress = create_semaph(semaphName);
    int semaphInitValue = semaph_value(semaphAdress);
    printf("\n\nUtworzono semafor z poczatkowa wartoscia %d\n\n", semaphInitValue);

    /* utworzenie pamieci dzielonej */

    /* fork procesu - proces potomny wykonywac bedzie program
       producenta, a proces macierzysty program konsumenta */
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            execlp("./producer.x", "./producer.x", argv[1], semaphName, /*shm adress*/ NULL);
            perror("execlp error");
            _exit(501);
        default:
            sleep(2);
    }

    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            execlp("./consumer.x", "./consumer.x", argv[2], semaphName, /*shm adress*/ NULL);
            perror("execlp error");
            _exit(502);
    }

    if(signal(SIGINT, removeEverything) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 2; i++)
    {
        if(waitpid(-1, NULL, 0) == -1)
        {
            perror("wait error");
            exit(403);
        }
    }

    /* atexit -  wywolanie funkcji usuwajacej semafor i zwalniajacej pamiec dzielona */
    if(atexit(removeEverything) != 0)
    {
        perror("error executing atexit function");
        exit(900);
    }

    return 0;
}