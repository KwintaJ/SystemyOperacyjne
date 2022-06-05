//############################################//
//                                            //
//    Jan Kwinta                DD.MM.YYYY    //
//                                            //
//                                            //
//    Projekt: Kolejki komunikatow Zadanie 8  //
//    Plik: client.c                          //
//                                            //
//    Program klienta                         //
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
char clientConnectionName[50];

/* funkcje zamykajace */
void closeClient()
{
    close_mq(clientDesc);
}

void closeConnectionToServer()
{
    close_mq(serverDesc);
    delete_mq(clientConnectionName);
}

void exiting()
{
    closeClient();
    closeConnectionToServer();
}

int main(int argc, char **argv)
{
    /* inicjalizacja generatora liczb pseudolosowych */
    time_t seed;
    srand(time(&seed));

    /* atrybuty kolejki komunikatow */ 
    struct mq_attr new_attr;
    new_attr.mq_flags = 0;
    new_attr.mq_maxmsg = 15;
    new_attr.mq_msgsize = QUEUELENGTH;
    new_attr.mq_curmsgs = 0;

    /* zmienne */
    struct mq_attr attributes;
    char sentMessage[QUEUELENGTH];
    char receivedMessage[QUEUELENGTH];
    char readText[20];

    pid_t ownPid = getpid();
    sprintf(clientConnectionName, "/%d", ownPid);

    /* otwarcie kolejek */
    clientDesc = create_mq(clientConnectionName, &new_attr);
    clientDesc = open_mq_readonly(clientConnectionName);

    serverDesc = open_mq_writeonly(QUEUENAME);

    /* wypisanie atrybutow kolejki */
    get_attr_of_mq(clientDesc, &attributes);
    printf("Client process is using message queue \"%s\" with attributes: \n", QUEUENAME);
    printf("    Descriptor: %d", clientDesc);
    printf("    Flags: %ld", attributes.mq_flags);
    printf("    Max number of messages in queue: %ld", attributes.mq_maxmsg); 
    printf("    Max message size: %ld bytes", attributes.mq_msgsize);

    /* komunikacja kilent - serwer */
    printf("Type your query: ");
    while(fgets(readText, sizeof(readText), stdin) != NULL)
    {
        sprintf(sentMessage, "%d %s", ownPid, readText);
        
        sleep(rand() % 6);
        send_thru_mq(serverDesc, sentMessage, QUEUELENGTH, 0);
        printf("Message sent to server\n");

        /*odczytanie komunikatu z serwera*/
        receive_thru_mq(clientDesc, receivedMessage, QUEUELENGTH);

        /*wypisanie komunikatu na konsolę*/
        printf("Answer received: %s\n\n\n", receivedMessage);

        printf("Type your next query: ");
    }

    printf("Client process exiting...\n");
    exit(EXIT_SUCCESS);

    atexit(exiting);
}