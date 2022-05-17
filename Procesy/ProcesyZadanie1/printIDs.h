#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#ifndef PRINTIDS
#define PRINTIDS

void printIDs()
{   
    uid_t UID = getuid(); // pobranie ID Uzytkownika
    gid_t GID = getgid(); // pobranie ID grupy Uzytkownika
    /* pobranie ID procesu, ID procesu macierzystego i ID lidera grupy */ 
    pid_t PID = getpid(), PPID = getppid(), PGID = getpgrp();

    /* wypisanie na wyjscie */
    printf("Process UID = %d   GID = %d   PID = %d   PPID = %d   PGID = %d\n", UID, GID, PID, PPID, PGID);
}

#endif