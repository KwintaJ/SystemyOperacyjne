//############################################//
//                                            //
//    Jan Kwinta                04.05.2022    //
//                                            //
//                                            //
//    Projekt: Semafory Zadanie 6             //
//    Plik: realisator.c                      //
//                                            //
//    Program realizujacy operacje krytyczne  //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

#include "semaph_lib.h"

void criticalSection()
{
    /* otwarcie pliku numer.txt do czytania */
    int inFileDesc;
    if((inFileDesc = open("numer.txt", O_RDONLY, 0644)) == -1)
    {
        perror("opening file error");
        _exit(604);
    }

    /* wczytanie liczby z pliku, wypisanie jej na ekran */
    char theNumber[50];
    int readBytes = read(inFileDesc, theNumber, 50);
    if(readBytes < 1)
    {
        perror("read from file error");
        _exit(605);
    }
    int theNumberInt = atoi(theNumber);
    printf("    Numer kontrolny = %d\n\n", theNumberInt);

    /* zamkniecie pliku numer.txt */
    if(close(inFileDesc) == -1)
    {
        perror("closing file error");
        _exit(606);
    }

    /* zawieszenie programu na losowa liczbe sekund */
    sleep((rand() % 5) + 1);

    /* zwiekszenie numeru kontrolnego */
    theNumberInt++;
    char theNumberIncremented[50];
    if(sprintf(theNumberIncremented, "%d", theNumberInt) < 0)
    {
        perror("sprintf error");
        _exit(607);
    }

    /* otwarcie pliku numer.txt do zapisu */
    int outFileDesc;
    if((outFileDesc = open("numer.txt", O_WRONLY, 0644)) == -1)
    {
        perror("opening file error");
        _exit(608);
    }

    /* zapisanie zwiekszonego numeru kontrolnego do pliku */
    if(write(outFileDesc, theNumberIncremented, strlen(theNumberIncremented)) == -1)
    {
        perror("file write error");
        _exit(609);
    }

    /* zamkniecie pliku numer.txt */
    if(close(outFileDesc) == -1)
    {
        perror("closing file error");
        _exit(610);
    }
}

int main(int argc, char **argv)
{
    char *semaphName = argv[2];
    int sectionNumber = atoi(argv[1]);

    /* otworzenie semafora przez proces */
    sem_t *semaph = open_semaph(semaphName);

    /* inicjalizacja generatora liczb pseudolosowych */
    time_t seed;
    srand(time(&seed));

    /* id procesu */
    pid_t ownPID = getpid();

    for(int i = 0; i < sectionNumber; i++)
    {
        /* wlasne sprawy */
        printf("Proces %d wykonuje zwykle operacje\n\n", ownPID);
        sleep((rand() % 5) + 1);

        printf("Wartosc semafora: %d\n\n", semaph_value(semaph));
        if(vrijmaken(semaph) != 0)
        {
            perror("semaphore error");
            _exit(701);
        }
        printf("Wartosc semafora: %d\n\n", semaph_value(semaph));
        
        /* sekcja krytyczna */
        printf("        Proces %d wykonuje sekcje krytyczna numer %d\n\n", ownPID, i + 1);
        
        criticalSection();

        printf("Wartosc semafora: %d\n\n", semaph_value(semaph));
       
        /* reszta */
        if(passeren(semaph) != 0)
        {
            perror("semaphore error");
            _exit(702);
        }
        printf("Wartosc semafora: %d\n\n", semaph_value(semaph));
        printf("Proces %d wykonuje zwykle operacje\n\n", ownPID);
    }

    return 0;
}