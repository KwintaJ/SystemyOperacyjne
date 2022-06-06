//############################################//
//                                            //
//    Jan Kwinta                06.06.2022    //
//                                            //
//                                            //
//    Projekt: Watki Zadanie 9                //
//    Plik: threads9.c                        //
//                                            //
//    Program wykonujacy wzajemne wykluczanie //
//    dla kilku watkow                        //
//                                            //
//############################################//

#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

/* zmienne globalne */
int controlValue = 0;
pthread_mutex_t processMutex;
int sectNum;
int threadsNum;

/* funkcja sprawdzajaca poprawnosc argumentow wywolania */
void argCheck(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("ERROR\nNiepoprawna liczba argumentow\nPatrz README");
        exit(EXIT_FAILURE);
    }

    if(atoi(argv[1]) < 1)
    {
        printf("ERROR\nNiepoprawna liczba watkow\nPatrz README");
        exit(EXIT_FAILURE);
    }

    if(atoi(argv[1]) > 20)
    {
        printf("ERROR\n Za duza liczba watkow\nPatrz README");
        exit(EXIT_FAILURE);
    }

    if(atoi(argv[2]) < 1)
    {
        printf("ERROR\nNiepoprawna liczba sekcji\nPatrz README");
        exit(EXIT_FAILURE);
    }
}

/*funkcja do ustawiania kursora na odpowiednim miejscu w terminalu*/
void goToXY(unsigned int x, unsigned int y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}

/* realizacja wzajemnego wykluczania dla watkow */
static void* exclusion(void *arg)
{
    int *ownID = arg;
    int localControlValue;
    goToXY(1, *ownID);
    printf("\033[32mThread with ID = %d was created\033[0m\n", *ownID);
    sleep((rand() % 3 ) + 2);


    for(int i = 0; i < sectNum; i++)
    {
        /* sekcja prywatna */
        goToXY(1, *ownID);
        printf("\033[33mThread %d is realising private section number %d\033[0m\n\n", *ownID, i + 1);
        sleep((rand() % 5 ) + 1);

        /* sekcja krytyczna */
        pthread_mutex_lock(&processMutex);
        goToXY(70, *ownID);
        localControlValue = controlValue;
        printf("\033[31mThread %d is realising critical section number %d. Control value of %d is incremented.\033[0m\n", *ownID, i + 1, localControlValue);
        localControlValue++;
        sleep((rand() % 6 ) + 1);
        controlValue = localControlValue;

        /* koniec sekcji krytycznej */
        pthread_mutex_unlock(&processMutex);
        goToXY(1, *ownID);
        printf("\033[32mThread %d ended its critical section\033[0m\n\n", *ownID);
        sleep(1);
    }

    return arg;
}

int main(int argc, char **argv)
{
    /* argumenty wywolania */
    argCheck(argc, argv);
    threadsNum = atoi(argv[1]);
    sectNum = atoi(argv[2]);

    /* inicjalizacja generatora liczb pseudolosowych */
    time_t seed;
    srand(time(&seed));

    /* inicjowanie mutexu i wypisanie jego adresu */
    if(pthread_mutex_init(&processMutex, NULL) != 0)
    {
        perror("initializing mutex error");
        exit(EXIT_FAILURE);
    }
    printf("\e[1;1H\e[2J");
    printf("Created mutex with address: %p\n", &processMutex);

    /* identyfikatory watkow */
    pthread_t threadsIdsArray[threadsNum];
    for(unsigned int i = 0; i < threadsNum; i++)
        threadsIdsArray[i] = i + 1;

    sleep(2); // zatrzymanie programu na 2 sekundy dla czytelnosci

    /* tworzenie watkow realizujacych funkcje exclusion */
    printf("\e[1;1H\e[2J");
    for(unsigned int i = 0; i < threadsNum; i++)
    {
        int *threadID = malloc(sizeof(int));
        *threadID = i + 1;
        if(pthread_create(&threadsIdsArray[i], NULL, &exclusion, (void *)threadID) != 0)
        {
            perror("creating new thread error");
            exit(EXIT_FAILURE);
        }
    }

    /* czekanie na wszystkie watki */
    for(unsigned int i = 0; i < threadsNum; i++)
    {
        if(pthread_join(threadsIdsArray[i], NULL) != 0)
        {
            perror("joining threads error");
            exit(EXIT_FAILURE);
        }
    }

    sleep(1); // zatrzymanie programu na sekunde dla czytelnosci
    printf("\e[1;1H\e[2J");

    /* po zakonczeniu wszystkich watkow realizujacych wzajemne wykluczanie
       watek glowny sprawdza wartosc kontrolna i zamyka mutex */
    printf("All threads ended. Control value is %d.\n", controlValue);
    printf("Control value should be equal to\n");
    printf("    number_of_threads * number_of_sections (%d * %d = %d)\n\n", threadsNum, sectNum, threadsNum * sectNum);

    if(pthread_mutex_destroy(&processMutex) != 0)
    {
        perror("deleting mutex error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}