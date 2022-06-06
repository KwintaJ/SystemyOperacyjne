//############################################//
//                                            //
//    Jan Kwinta                06.06.2022    //
//                                            // 
//                                            //
//    Projekt: Kolejki komunikatow Zadanie 8  //
//    Plik: mqueue_lib.c                      //
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

#include "mqueue_lib.h"

mqd_t create_mq(const char *name, struct mq_attr *attr)
{
    mqd_t desc;
    desc = mq_open(name, O_CREAT | O_EXCL | O_RDWR, 0666, NULL);
    if(desc == -1)
    {
        perror("creating message queue error");
        exit(EXIT_FAILURE);
    }
    return desc;
}

mqd_t open_mq_readonly(const char *name)
{
    mqd_t desc;
    desc = mq_open(name, O_RDONLY);
    if(desc == -1)
    {
        perror("opening message queue error");
        exit(EXIT_FAILURE);
    }
    return desc;
}

mqd_t open_mq_writeonly(const char *name)
{
    mqd_t desc;
    desc = mq_open(name, O_WRONLY);
    if(desc == -1)
    {
        perror("opening message queue error");
        exit(EXIT_FAILURE);
    }
    return desc;
}

void send_thru_mq(mqd_t desc, const char *message, int buffersize, int priority)
{
    if(mq_send(desc, message, buffersize, priority) == -1)
    {
        perror("sending message error");
        exit(EXIT_FAILURE);
    }
}

void receive_thru_mq(mqd_t desc, char *buffer, size_t buffersize)
{
    if(mq_receive(desc, buffer, buffersize, NULL) == -1)
    {
        perror("recieving message error");
        exit(EXIT_FAILURE);
    }
}

void get_attr_of_mq(mqd_t desc, struct mq_attr *attr)
{
    if(mq_getattr(desc, attr) ==-1)
    {
        perror("geting attribute error");
        exit(EXIT_FAILURE);
    }
}

void close_mq(mqd_t desc)
{
    if(mq_close(desc) == -1)
    {
        perror("closing message queue error");
        exit(EXIT_FAILURE);
    }
}

void delete_mq(const char *name)
{
    if(mq_unlink(name) == -1)
    {
        perror("unlinking message queue error");
        exit(EXIT_FAILURE);
    }
}
