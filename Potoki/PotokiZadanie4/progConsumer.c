//############################################//
//                                            //
//    Jan Kwinta                05.04.2022    //
//                                            //
//                                            //
//    Projekt: Potoki Zadanie 4               //
//    Plik: progConsumer.c                    //
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
    if(sprintf(notice, "\nUruchomienie konsumenta\nKonsument bedzie pobieral dane w paczkach po %dB\n\n", packageSize) < 0)
    {
        perror("sprintf error");
        _exit(305);
    }
    if(write(STDOUT_FILENO, notice, strlen(notice)) == -1)
    {
        perror("stdout write error");
        _exit(603);
    }

    /* numery dekryptorow potoku */
    int pipeRead = atoi(argv[2]);
    int pipeWrite = atoi(argv[3]);

    /* zwolnienie nieuzywanego konca potoku: do zapisywania */
    if(close(pipeWrite) == -1)
    {
        perror("closing write descriptor error");
        _exit(703);
    }

    /* otwarcie pliku do zapisu, jezeli nie istnieje stworzenie go*/
    int fdesc;
    if((fdesc = open(argv[1], O_WRONLY | O_CREAT, 0644)) == -1)
    {
        perror("opening file error");
        _exit(803);
    }
    char product[F_MAX];

    /* czytanie z potoku, zapis do pliku */
    int readBytes = read(pipeRead, product, packageSize);
    if(readBytes == -1)
    {
        perror("read from pipe error");
        _exit(904);
    }
    while(readBytes > 0)
    {
        /* wypisanie komunikatu o pobieranych danych */
        char announcement[400];
        if(sprintf(announcement, " Konsument:\n    Wczytana ilosc bajtow: %d\n    Pobierane dane: ", readBytes) < 0)
        {
            perror("sprintf error");
            _exit(306);
        }
        if(write(STDOUT_FILENO, strcat(announcement, product), strlen(announcement) + readBytes) == -1 || write(STDOUT_FILENO, "\n\n", 2) == -1)
        {
            perror("stdout write error");
            _exit(604);
        }

        /* zapis danych do pliku */
        if(write(fdesc, product, readBytes) == -1)
        {
            perror("pipe write error");
            _exit(905);
        }

        /* wylosowanie czasu uspienia z przedzialu [1; 4] sekund */
        int timeToSleep = (rand() % 4) + 1;
        sleep(timeToSleep);

        /* przeczytanie kolejnego pakietu z potoku */
        readBytes = read(pipeRead, product, packageSize);
        if(readBytes == -1)
        {
            perror("read from pipe error");
            _exit(906);
        }
    }

    /* zwolnienie deskryptora potoku */
    if(close(pipeRead) == -1)
    {
        perror("closing read descriptor error");
        _exit(704);
    }

    /* zamkniecie pliku do zapisu */
    if(close(fdesc) == -1)
    {
        perror("closing file error");
        _exit(804);
    }

    return 0;
}