//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: consumer.c                        //
//                                            //
//    Program konsument                       //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "memory_lib.h"

#define NUMBUF 5
#define NUMELM 20

typedef struct
{
    char buffer[NUMBUF][NUMELM];
    int push, get;
} shmSegment;

int chceckIfNotEndOfString(shmSegment transfer, int bufferNum, int *end)
{
    for(int i = 0; i < NUMELM; i++)
    {
        if(transfer.buffer[bufferNum][i] == '\0')
        {
            *end = i;
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    /* nazwy */
    char *fileName = argv[1];
    char *semaphName = argv[2];
    char *shmObjName = argv[3];

    /* pliku do zapisu */
    int fdesc = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fdesc == -1)
    {
        perror("opening file error");
        _exit(EXIT_FAILURE);
    }

    /* semafor, pamiec dzielona */
    sem_t *semaph = open_semaph(semaphName);
    int shmObjAdress = open_shm_obj(shmObjName);

    shmSegment *transfer = (shmSegment *) map_shm_obj(sizeof(shmSegment), shmObjAdress);
    transfer->get = 0; // poczatkowo indeks = 0

    printf("Utworzono proces konsumenta\n");
    printf("    Konsument odbiera dane w paczkach po %d bajtow\n", NUMELM);
    printf("    Konsument ma dostep do pamieci dzielonej o rozmiarze %ld\n", sizeof(shmSegment));
    printf("    i adresie %d\n\n", shmObjAdress);


    /* odbieranie towaru przez pamiec dzielona */
    int readBytes, potentialEnd, lastIndex;
    do
    {
        /* opuszczenie semafora */
        vrijmaken(semaph);
        printf("Wartosc semafora: %d\n", semaph_value(semaph));

        /* czytanie z pamieci dzielonej i zapis do pliku*/
        if(chceckIfNotEndOfString(*transfer, transfer->get, &potentialEnd) == 0)
            readBytes = write(fdesc, transfer->buffer[transfer->get], potentialEnd);
        else
            readBytes = write(fdesc, transfer->buffer[transfer->get], NUMELM);

        if(readBytes == -1)
        {
            perror("write error\n");
             _exit(EXIT_FAILURE);
        }

        printf("Proces konsumenta:\n");
        printf("    Biezacy indeks elementu bufora: %d\n", transfer->get);
        printf("    Ilosc odczytanych bajtow: %d\n - odczytane dane", readBytes);

        if(write(STDOUT_FILENO, transfer->buffer[transfer->get], readBytes) == -1)
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }
        printf("\n");

        /* zwiększenie indeksu */
        lastIndex = transfer->get;
        transfer->get = (transfer->get + 1) % NUMBUF;

        /* podniesienie semafora */
        passeren(semaph);
        printf("Wartosc semafora: %d\n", semaph_value(semaph));

        sleep(1);
        printf("\n");
        printf("\n");
    }
    while(chceckIfNotEndOfString(*transfer, lastIndex, &potentialEnd) != 0);

    /* zamkniecie pliku, semaforów i obiektu pamięci dzielonej */
    if(close(fdesc) == -1)
    {
        perror("closing file error\n");
        _exit(EXIT_FAILURE);
    }

    close_semaph(semaph);
    close_shm_obj(shmObjAdress);

    printf("\n\n\nProces konsumenta zostal zakonczony\n\n");
    _exit(EXIT_SUCCESS);
}
