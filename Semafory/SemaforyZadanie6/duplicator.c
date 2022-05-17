//############################################//
//                                            //
//    Jan Kwinta                04.05.2022    //
//                                            //
//                                            //
//    Projekt: Semafory Zadanie 6             //
//    Plik: duplicator.c                      //
//                                            //
//    Program powielajacy realizatora         //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "semaph_lib.h"

const char *semaphName = "mysemaphor";

/* funkcja sprawdzajaca poprawnosc argumentow wywolania programu */
void argCheck(int argc, char **argv)
{
    /* liczba argumentow ==3 */
    if(argc != 4)
    {
        printf("ERROR\nNiepoprawna liczba argumentow\nPatrz README\n");
        exit(101);
    }
    /* rozszerzenie pliku realizujacego == .x*/
    if(argv[1][strlen(argv[1]) - 1] != 'x' || argv[1][strlen(argv[1]) - 2] != '.')
    {
        printf("ERROR\nNiepoprawne rozszerzenie\nPatrz README\n");
        exit(102);
    }
    /* liczba powielen i liczba sekcji >0 */
    if(atoi(argv[2]) < 1)
    {
        printf("ERROR\nNiepoprawne liczba powielen\nPatrz README\n");
        exit(103);
    }
    if(atoi(argv[3]) < 1)
    {
        printf("ERROR\nNiepoprawne liczba sekcji\nPatrz README\n");
        exit(104);
    }
}

/* funkcja usuwajaca semafor */
void removeSemaph()
{
    delete_semaph(semaphName);
}

int main(int argc, char **argv)
{
    /* utworzenie semafora */
    sem_t *semaphAdress = create_semaph(semaphName);
    int semaphInitValue = semaph_value(semaphAdress);
    printf("\n\nUtworzono semafor z poczatkowa wartoscia %d\n\n", semaphInitValue);

    /* sprawdzenie argumentow */
    argCheck(argc, argv);

    /* otwarcie pliku numer.txt, jezeli nie istnieje stworzenie go */
    int fdesc;
    if((fdesc = open("numer.txt", O_WRONLY | O_CREAT, 0644)) == -1)
    {
        perror("opening file error");
        exit(601);
    }
    /* zapisanie 0 do pliku */
    if(write(fdesc, "0", 1) == -1)
    {
        perror("file write error");
        exit(602);
    }
    /* zamkniecie pliku numer.txt */
    if(close(fdesc) == -1)
    {
        perror("closing file error");
        exit(603);
    }

    char realisPath[50]; // sciezka do programu realizujacego
    sprintf(realisPath, "./%s", argv[1]);
    printf("%s\n", realisPath);

    int processNumber = atoi(argv[2]); // liczba powielen
    int sectionsNumber = atoi(argv[3]); // liczba sekcji

    for(int i = 0; i < processNumber; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(201);
            case 0:
                if(execlp(realisPath, argv[1], argv[3], semaphName) != 0)
                {
                    perror("execlp error");
                    _exit(301);
                }
            default:
                if(signal(SIGINT, removeSemaph) == SIG_ERR)
                {
                    perror("signal error");
                    exit(EXIT_FAILURE);
                }
                sleep(1);
        }
    }

    if(signal(SIGINT, removeSemaph) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < processNumber; i++)
    {
        if(waitpid(-1, NULL, 0) == -1)
        {
            perror("wait error");
            exit(403);
        }
    }
    
    /* otwarcie pliku numer.txt */
    int fdesc2;
    if((fdesc2 = open("numer.txt", O_RDONLY, 0644)) == -1)
    {
        perror("opening file error");
        exit(611);
    }
    /* wczytanie numeru z pliku i wypisanie go */
    char theNumber[50];
    int readBytes = read(fdesc2, theNumber, 50);
    if(readBytes < 1)
    {
        perror("read from file error");
        _exit(612);
    }
    printf("Koncowa wartosc numeru kontrolnego wyniosla %s\n", theNumber);
    printf("Oczekiwana wartosc numeru kontrolnego to liczbaProcesow * liczbaSekcji czyli %d\n\n", processNumber * sectionsNumber);
    /* zamkniecie pliku numer.txt */
    if(close(fdesc2) == -1)
    {
        perror("closing file error");
        exit(613);
    }

    /* atexit -  wywolanie funkcji usuwajacej semafor */
    if(atexit(removeSemaph) != 0)
    {
        perror("error executing atexit function");
        exit(900);
    }

    return 0;
}