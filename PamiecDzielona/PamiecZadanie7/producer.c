//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: producer.c                        //
//                                            //
//    Program producent                       //
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

int main(int argc, char **argv)
{
    /* nazwy */
    char *fileName = argv[1];
    char *semaphName = argv[2];
    char *shmObjName = argv[3];

    /* plik do odczytu */
    int fdesc = open(fileName, O_RDONLY, 0666);
    if(fdesc == -1)
    {
        perror("opening file error");
        _exit(EXIT_FAILURE);
    }

    /* semafor, pamiec dzielona */
    sem_t *semaph = open_semaph(semaphName);
    int shmObjAdress = open_shm_obj(shmObjName);

    shmSegment *transfer = (shmSegment *) map_shm_obj(sizeof(shmSegment), shmObjAdress);
    transfer->push = 0; // poczatkowo indeks = 0

    printf("Utworzono proces producenta\n");
    printf("    Producent przesyla dane w paczkach po %d bajtow\n", NUMELM);
    printf("    Producent ma dostep do pamieci dzielonej o rozmiarze %ld\n", sizeof(shmSegment));
    printf("    i adresie %d\n\n", shmObjAdress);


    /* przekazywanie towaru przez pamiec dzielona */
    int readBytes;
    do
    {
        /* opuszczenie semafora */
        vrijmaken(semaph);
        printf("Wartosc semafora: %d\n", semaph_value(semaph));

        /* czytanie z pliku do obiektu pamieci dzielonej */
        readBytes = read(fdesc, transfer->buffer[transfer->push], NUMELM);
        if(readBytes == -1)
        {
            perror("read error\n");
            _exit(EXIT_FAILURE);
        }
        if(readBytes < NUMELM)
        {
            transfer->buffer[transfer->push][readBytes] = '\0';
        }

        printf("Proces producenta:\n");
        printf("    Biezacy indeks elementu bufora: %d\n", transfer->push);
        printf("    Ilosc przeslanych bajtow: %d\n - przeslane dane", readBytes);

        if(write(STDOUT_FILENO, transfer->buffer[transfer->push], readBytes) == -1)
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }
        printf("\n");

        /* zwiększenie indeksu */
        transfer->push = (transfer->push + 1) % NUMBUF;

        /* podniesienie semafora */
        passeren(semaph);
        printf("Wartosc semafora: %d\n", semaph_value(semaph));

        sleep(1);
        printf("\n");
        printf("\n");
    }
    while(readBytes == NUMELM);

    /* zamkniecie pliku, semaforów i obiektu pamięci dzielonej */
    if(close(fdesc) == -1)
    {
        perror("closing file error\n");
        _exit(EXIT_FAILURE);
    }

    close_semaph(semaph);
    close_shm_obj(shmObjAdress);

    printf("\n\n\nProces producenta zostal zakonczony\n\n");
    _exit(EXIT_SUCCESS);
}
