#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#ifndef ARGERRORS
#define ARGERRORS

/*  funkcja sprawdzajaca poprawnosc argumentow wywolania 
    przyjmuje: liczbe argumentow i liste argumentow*/
int argErrors(int argc, char **argv)
{
    /* sprawdzenie czy liczba argumentow jest poprawna (rowna 3) */
    if(argc != 3)
    {
        printf("ERROR:\nNiepoprawna liczba argumentow\nPatrz README\n");
        return -1;
    }
    
    /* sprawdzenie czy argument opcji obslugi jest poprawny (sa tylko 3 legalne opcje: default, ignore, handle) */
    if(!(strcmp(argv[1], "default") == 0 || strcmp(argv[1], "ignore") == 0 || strcmp(argv[1], "handle") == 0)) 
    {
        printf("ERROR:\nNiepoprawny argument opcji obslugi\nPatrz README\n");
        return -2;
    }

    /* sprawdzenie czy numer procesu jest poprawny (pomiedzy 1 a 64) */
    if(atoi(argv[2]) > 64 || atoi(argv[2]) < 1)
    {
        printf("ERROR:\nNiepoprawny argument numeru sygnalu\nPatrz README\n");
        return -3;
    }
    return 0;
}

#endif