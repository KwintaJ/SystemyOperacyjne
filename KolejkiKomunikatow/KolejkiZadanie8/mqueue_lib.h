//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Kolejki komunikatow Zadanie 8  //
//    Plik: mqueue_lib.h                      //
//                                            //
//    Biblioteka uzytecznych operacji         //
//    kolejek komunikatów                     //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#ifndef QUEUENAME
#define QUEUENAME "/serverQueue"
#endif

#ifndef QUEUELENGTH
#define QUEUELENGTH 50
#endif

#ifndef MQUEUE_LIB
#define MQUEUE_LIB

/* tworzenie i otwieranie kolejki komunikatow */
mqd_t create_mq(const char*, struct mq_attr*);
mqd_t open_mq_readonly(const char*);
mqd_t open_mq_writeonly(const char*);

/* obsluga kolejki */
void send_thru_mq(mqd_t, const char*, int, int);
void receive_thru_mq(mqd_t, char*, int);
void get_attr_of_mq(mqd_t, struct mq_attr*);
void set_attr_of_mq(mqd_t, struct mq_attr*, struct mq_attr*);

/* zamykanie i usuwanie kolejki */
void close_mq(mqd_t);
void delete_mq(const char*);

#endif
