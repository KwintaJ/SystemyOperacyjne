//############################################//
//                                            //
//    Jan Kwinta                06.06.2022    //
//                                            //
//                                            //
//    Projekt: Kolejki komunikatow Zadanie 8  //
//    Plik: server.c                          //
//                                            //
//    Program serwera                         //
//                                            //
//############################################//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <mqueue.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "mqueue_lib.h"

mqd_t serverDesc, clientDesc;

/* funkcje zamykajace */
void closeServer()
{
    close_mq(serverDesc);
    delete_mq(QUEUENAME);
}

void exiting()
{
    atexit(closeServer);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    /* inicjalizacja generatora liczb pseudolosowych */
    time_t seed;
    srand(time(&seed));

    /* atrybuty kolejki komunikatow */ 
    struct mq_attr new_attr;
    new_attr.mq_flags = 0;
    new_attr.mq_maxmsg = 20;
    new_attr.mq_msgsize = QUEUELENGTH;
    new_attr.mq_curmsgs = 0;

    /* zmienne */
    struct mq_attr attributes;

    char receivedMessage[QUEUELENGTH];
    char messageToClient[QUEUELENGTH];

    pid_t clientPid;
    int number1, number2;
    char operator;
    char connectionToClientName[10];

    /* otworzenie kolejki */
    serverDesc = create_mq(QUEUENAME, &new_attr);
    serverDesc = open_mq_readonly(QUEUENAME);

    /* wypisanie atrybutow kolejki */
    get_attr_of_mq(serverDesc, &attributes);
    printf("Server has reated a queue \"%s\" with atributes:\n", QUEUENAME);
    printf("    Descriptor: %d\n", serverDesc);
    printf("    Flags: %ld\n", attributes.mq_flags);
    printf("    Max number of messages in queue: %ld\n", attributes.mq_maxmsg); 
    printf("    Max message size: %ld bytes\n\n", attributes.mq_msgsize);

    /* obsługa sygnału */
    if (signal(SIGINT, exiting) == SIG_ERR)
    {
        perror("signal handling error");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        /* odczytywanie wiadomości klienta */
        printf("Sever is waiting for a message\n\n");

        receive_thru_mq(serverDesc, receivedMessage, attributes.mq_msgsize);
        printf("Received message: %s\n", receivedMessage);

        sscanf(receivedMessage, "%d %d%c%d", &clientPid, &number1, &operator, &number2);
        sprintf(connectionToClientName, "/%d", clientPid);

        printf("Calculating query: %d %c %d\n", number1, operator, number2);

        /* obliczenia */
        switch(operator)
        {
            case '+':
                sprintf(messageToClient, "%d", number1 + number2);
                break;

            case '-':
                sprintf(messageToClient, "%d", number1 - number2);
                break;
                
            case '*':
                sprintf(messageToClient, "%d", number1 * number2);
                break;

            case '/':
                sprintf(messageToClient, "%g", (double)(number1 / number2));
                break;

            default:
                sprintf(messageToClient, "Result not calculated: wrong operator");
        }

        printf("Result was calculated and the message is sent back\n\n");

        /* wysylanie wyniku do klienta */
        clientDesc = open_mq_writeonly(connectionToClientName);
        send_thru_mq(clientDesc, messageToClient, QUEUELENGTH, 0);
        close_mq(clientDesc);
    }

    atexit(closeServer);
}
