//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: memory_lib.h                      //
//                                            //
//    Biblioteka uzytecznych operacji         //
//    pamieci dzielonej - prototypy           //
//                                            //
//############################################//

#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#ifndef MEMORY_LIB
#define MEMORY_LIB

/* tworzenie, otwieranie semafora */
sem_t* create_semaph(const char*);
sem_t* open_semaph(const char *);

/* zamykanie, usuwanie semafora */
void close_semaph(sem_t*);
void delete_semaph(const char*);

/* podnoszenie, opuszczanie semafora */
int vrijmaken(sem_t*);
int passeren(sem_t*);

/* wartosc semafora */
int semaph_value(sem_t*);

/* tworzenie, otwieranie obiektu pamieci dzielonej */
int create_shm_obj(const char*);
int open_shm_bbj(const char*);

/* zamykanie, usuwanie obiektu pamieci dzielonej */
void close_shm_obj(int);
void delete_shm_obj(const char*);


#endif