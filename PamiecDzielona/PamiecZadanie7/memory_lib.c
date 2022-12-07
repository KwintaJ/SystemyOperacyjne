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
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "memory_lib.h"

sem_t* create_semaph(const char *name)
{
    sem_t *semaph_address = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
    if(semaph_address == SEM_FAILED)
    {
        perror("creating semaphore error");
        exit(-1);
    }
    return semaph_address;
}

sem_t* open_semaph(const char *name)
{
    sem_t *semaph_address = sem_open(name, 0);
    if(semaph_address == SEM_FAILED)
    {
        perror("opening semaphore error");
        exit(-2);
    }
    return semaph_address;
}

void close_semaph(sem_t *address)
{
    if(sem_close(address) == -1)
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

int vrijmaken(sem_t *address)
{
    if(sem_wait(address) == -1)
    {
        perror("waiting semaphore error");
        return -5;
    }
    return 0;
}

int passeren(sem_t *address)
{
    if(sem_post(address) == -1)
    {
        perror("posting semaphore error");
        return -6;
    }
    return 0;
}

int semaph_value(sem_t *address)
{
    int val;
    int *valPtr = &val;
    if(sem_getvalue(address, valPtr) == -1)
    {
        perror("error getting semaphore value");
        exit(-7);
    }
    return val;
}

int create_shm_obj(const char *name)
{
    int shmObjDesc = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0644);
    if(shmObjDesc == -1)
    {
        perror("error creating shm object");
        exit(-8);
    }
    return shmObjDesc;
}

int open_shm_obj(const char* name)
{
    int shmObjDesc = shm_open(name, O_RDWR, 0644);
    if(shmObjDesc == -1)
    {
        perror("error opening shm object");
        exit(-9);
    }
    return shmObjDesc;
}

void truncate_shm_obj(int desc)
{
    if(ftruncate(desc, 500) == -1)
    {
        perror("truncating shm object error");
        exit(-10);
    }
}

void *map_shm_obj(size_t length, int desc)
{
    void *address = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
    if (address == MAP_FAILED)
    {
        perror("maping shm error");
        exit(-1);
    }
    return address;
}

void close_shm_obj(int desc)
{
    if(close(desc) == -1)
    {
        perror("error closing shm object");
        exit(-20);
    }
}

void delete_shm_obj(const char *name)
{
    if(shm_unlink(name) == -1)
    {
        perror("error deleting shm object");
        exit(-21);
    }
}
