//############################################//
//                                            //
//    Jan Kwinta                05.04.2022    //
//                                            //
//                                            //
//    Projekt: Potoki Zadanie 4               //
//    Plik: progProducer.c                    //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

const int F_MAX = 500;

int main(int argc, char **argv)
{
    /* inicjalizacja generatora liczb pseudolosowych */
    time_t seed;
    srand(time(&seed));

    /* losowanie rozmiaru pakietu z przedzialu [10; 40] */
    int packageSize = (rand() % 31) + 10;

    /* wyswietlenie komunikatu o uruchomieniu programu i rozmiarze pakietow danych */
    char notice[300];
    if(sprintf(notice, "\nUruchomienie producenta\nProducent bedzie wysylal dane w paczkach po %dB\n\n", packageSize) < 0)
    {
        perror("sprintf error");
        _exit(303);
    }
    if(write(STDOUT_FILENO, notice, strlen(notice)) == -1)
    {
        perror("stdout write error");
        _exit(601);
    }

    /* numery dekryptorow potoku */
    int pipeRead = atoi(argv[2]);
    int pipeWrite = atoi(argv[3]);

    /* zwolnienie nieuzywanego konca potoku: do czytania */
    if(close(pipeRead) == -1)
    {
        perror("closing read descriptor error");
        _exit(701);
    }

    /* otwarcie pliku do czytania */
    int fdesc;
    if((fdesc = open(argv[1], O_RDONLY, 0644)) == -1)
    {
        perror("opening file error");
        _exit(801);
    }
    if(write(STDOUT_FILENO, strcat(announcement, product), strlen(announcement) + readBytes) == -1 || write(STDOUT_FILENO, "\n\n", 2) == -1)
    {
        perror("stdout write error");
        _exit(604);
    }

    /* czytanie z pliku, przesylanie do potoku */
    int readBytes = read(fdesc, product, packageSize);
    if(readBytes == -1)
    {
        perror("read from file error");
        _exit(901);
    }
    while(readBytes > 0)
    {
        /* wypisanie komunikatu o przesylanych danych */
        char announcement[400];
        if(sprintf(announcement, " Producent:\n    Wczytana ilosc bajtow: %d\n    Przesylane dane: ", readBytes) < 0)
        {
            perror("sprintf error");
            _exit(304);
        }
        if(write(STDOUT_FILENO, strcat(announcement, product), strlen(announcement) + readBytes) == -1 || write(STDOUT_FILENO, "\n\n", 2) == -1)
        {
            perror("stdout write error");
            _exit(602);
        }

        /* przeslanie danych potokiem */
        if(write(pipeWrite, product, readBytes) == -1)
        {
            perror("pipe write error");
            _exit(902);
        }

        /* wylosowanie czasu uspienia z przedzialu [1; 3] sekund */
        int timeToSleep = (rand() % 3) + 1;
        sleep(timeToSleep);

        /* przeczytanie kolejnego pakietu z pliku */
        readBytes = read(fdesc, product, packageSize);
        if(readBytes == -1)
        {
            perror("read from file error");
            _exit(903);
        }
    }

    /* zwolnienie deskryptora potoku */
    if(close(pipeWrite) == -1)
    {
        perror("closing write descriptor error");
        _exit(702);
    }

    /* zamkniecie pliku do czytania */
    if(close(fdesc) == -1)
    {
        perror("closing file error");
        _exit(802);
    }

    return 0;
}