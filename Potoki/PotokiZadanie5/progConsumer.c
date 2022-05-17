//############################################//
//                                            //
//    Jan Kwinta                05.04.2022    //
//                                            //
//                                            //
//    Projekt: Potoki Zadanie 5               //
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
char *pipePath;

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

    /* otwarcie pliku do zapisu, jezeli nie istnieje stworzenie go*/
    int fileDesc;
    if((fileDesc = open(argv[1], O_WRONLY | O_CREAT, 0644)) == -1)
    {
        perror("opening file error");
        _exit(802);
    }

    /* otwarcie potoku FIFO */
    int fifoDesc;
    if((fifoDesc = open(argv[2], O_RDONLY, 0644)) == -1)
    {
        perror("opening fifo pipe error");
        _exit(802);
    }

    char product[F_MAX];

    /* czytanie z potoku, zapis do pliku */
    int readBytes = read(fifoDesc, product, packageSize);
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
        if(write(fileDesc, product, readBytes) == -1)
        {
            perror("pipe write error");
            _exit(905);
        }

        /* wylosowanie czasu uspienia z przedzialu [1; 4] sekund */
        int timeToSleep = (rand() % 4) + 1;
        sleep(timeToSleep);

        /* przeczytanie kolejnego pakietu z potoku */
        readBytes = read(fifoDesc, product, packageSize);
        if(readBytes == -1)
        {
            perror("read from pipe error");
            _exit(906);
        }
    }

    /* zamkniecie pliku do zapisu */
    if(close(fileDesc) == -1)
    {
        perror("closing read descriptor error");
        _exit(803);
    }

    /* zamkniecie potoku */
    if(close(fifoDesc) == -1)
    {
        perror("closing read descriptor error");
        _exit(804);
    }

    return 0;
}