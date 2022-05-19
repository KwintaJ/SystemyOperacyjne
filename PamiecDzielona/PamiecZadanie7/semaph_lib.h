//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Pamiec dzielona Zadanie 7      //
//    Plik: semaph_lib.h                      //
//                                            //
//    Biblioteka uzytecznych operacji         //
//    na semaforach - prototypy               //
//                                            //
//############################################//

#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef SEMAPH_LIB
#define SEMAPH_LIB

/* tworzenie, otwieranie semafora */
sem_t* create_semaph(const char*);
sem_t* open_semaph(const char *name);

/* zamykanie, usuwanie semafora */
void close_semaph(sem_t*);
void delete_semaph(const char*);

/* podnoszenie, opuszczanie semafora */
int vrijmaken(sem_t*);
int passeren(sem_t*);

/* wartosc semafora */
int semaph_value(sem_t*);

#endif