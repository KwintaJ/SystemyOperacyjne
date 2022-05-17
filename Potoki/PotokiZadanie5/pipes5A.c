//############################################//
//                                            //
//    Jan Kwinta                05.04.2022    //
//                                            //
//                                            //
//    Projekt: Potoki Zadanie 5               //
//    Plik: pipes5A.c                         //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

char *pipePath;

/* funkcja usuwajaca potok nazwany */
void removePipe()
{
    unlink(pipePath);
}

/* prototyp funkcji mkfifo */
int mkfifo(const char *path, mode_t mode);

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


int main(int argc, char **argv)
{

    /* sprawdzenie argumentow */
    argCheck(argc, argv);

    pipePath = argv[3];

    /* utowrzenie potoku nazwanego FIFO */
    if(mkfifo(argv[3], 0644) == -1)
    {
        perror("creating fifo pipe error");
        exit(201);
    }

    if(signal(SIGINT, removePipe) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    /* dwukrotny fork procesu - jeden  proces potomny wykonywac
       bedzie program producenta, a drugi program konsumenta */
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            if(execlp("./progProducer.x", "./progProducer.x", argv[1], argv[3], NULL) == -1)
            {
                perror("execlp error");
                _exit(501);
            }
        default:
            if(signal(SIGINT, removePipe) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            sleep(2);
    }

    pid_t child = fork();
    switch(child)
    {
        case -1:
            perror("fork error");
            exit(401);
        case 0:
            if(execlp("./progConsumer.x", "./progConsumer.x", argv[2], argv[3], NULL) == -1)
            {
                perror("execlp error");
                _exit(502);
            }
        default:
            if(signal(SIGINT, removePipe) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            if(waitpid(child, NULL, 0) == -1)
            {
                perror("wait error");
                _exit(503);
            }
    }
            

    /* atexit -  wywolanie funkcji usuwajacej potok nazwany */    
    if(atexit(removePipe) != 0)
    {
        perror("error executing atexit function");
        exit(800);
    }

    return 0;
}