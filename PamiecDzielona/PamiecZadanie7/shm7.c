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
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "memory_lib.h"

#define NUMBUF 5
#define NUMELM 20

const char *semaphName = "prodConsSemaphor";
const char *shmObjName = "/productSpace";

struct shmSegment
{
    char buffer[NUMBUF][NUMELM];
    int left, right;
};

/* funkcja sprawdzajaca poprawnosc argumentow uruchomienia */
void argCheck(int argc, char **argv)
{
    /* sprawdzenie czy ilosc argumentow jest poprawna */
    if(argc != 4)
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

/* funkcja wywolywana na koncu programu 
   usuwajaca semafor i obiekt pamieci dzielonej */
void removeEverything()
{
    delete_semaph(semaphName);
    delete_shm_obj(shmObjName);
}

int main(int argc, char **argv)
{
    /* sprawdzenie argumentow */
    argCheck(argc, argv);

    /* utworzenie semafora */
    sem_t *semaphAdress = create_semaph(semaphName);
    int semaphInitValue = semaph_value(semaphAdress);
    printf("\n\nUtworzono semafor z poczatkowa wartoscia %d\n\n", semaphInitValue);

    /* utworzenie obiektu pamieci dzielonej */
    create_shm_obj(shmObjName);

    /* nazwy plikow wykonywalnych producenta i konsumenta */
    char prodExec[50];
    sprintf(prodExec, "./producer%s.x", argv[3]);

    char consExec[50];
    sprintf(consExec, "./consumer%s.x", argv[3]);

    /* fork - dwa procesy potomne beda wykonywac programy
       producenta i konsumenta */
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            execlp(prodExec, "producer", argv[1], semaphName, /*shm adress*/ NULL);
            perror("execlp error");
            _exit(501);
        default:
            sleep(2);
    }

    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(402);
        case 0:
            execlp(consExec, "consumer", argv[2], semaphName, /*shm adress*/ NULL);
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