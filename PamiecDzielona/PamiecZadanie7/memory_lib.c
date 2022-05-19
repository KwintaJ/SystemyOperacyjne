//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: memory_lib.c                      //
//                                            //
//    Biblioteka uzytecznych operacji         //
//    pamieci dzielonej                       //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "memory_lib.h"

sem_t* create_semaph(const char *name)
{
    sem_t *semaph_adress = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
    if(semaph_adress == SEM_FAILED)
    {
        perror("creating semaphore error");
        exit(-1);
    }
    return semaph_adress;
}

sem_t* open_semaph(const char *name)
{
    sem_t *semaph_adress = sem_open(name, 0);
    if(semaph_adress == SEM_FAILED)
    {
        perror("opening semaphore error");
        exit(-2);
    }
    return semaph_adress;
}

void close_semaph(sem_t *adress)
{
    if(sem_close(adress) == -1)
    {
        perror("closing semaphore error");
        exit(-3);
    }
}

void delete_semaph(const char *name)
{
    if(sem_unlink(name) == -1)
    {
        perror("deleting semaphore error");
        exit(-4);
    }
}

int vrijmaken(sem_t *adress)
{
    if(sem_wait(adress) == -1)
    {
        perror("waiting semaphore error");
        return -5;
    }
    return 0;
}

int passeren(sem_t *adress)
{
    if(sem_post(adress) == -1)
    {
        perror("posting semaphore error");
        return -6;
    }
    return 0;
}

int semaph_value(sem_t *adress)
{
    int val;
    int *valPtr = &val;
    if(sem_getvalue(adress, valPtr) == -1)
    {
        perror("error getting semaphore value");
        exit(-7);
    }
    return val;
}

int create_shm_obj(const char *name)
{
	int shmObjDesc = shm_open(name, O_CREAT | O_EXCL, 0644);
	if(shmObjDesc == -1)
	{
		perror("error creating shm object");
		exit(-8);
	}
	return shmObjDesc;
}

int open_shm_bbj(const char* name)
{
	int shmObjDesc = shm_open(name, 0, 0644);
	if(shmObjDesc == -1)
	{
		perror("error opening shm object");
		exit(-9);
	}
	return shmObjDesc;
}

void close_shm_obj(int desc)
{
	if(close(desc) == -1)
	{
		perror("error closing shm object");
		exit(-10);
	}
}

void delete_shm_obj(const char *name)
{
	if(shm_unlink(name) == -1)
	{
		perror("error deleting shm object");
		exit(-11);
	}
}
