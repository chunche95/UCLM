
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <mqueue.h>
#include <definitions.h>

// Modulo principal
int main(int argc,char *argv[]){

    // Define variables locales
    int pid = getpid();
    //TODO
    // Control de parametros de entrada
    if ( argc != 1 ) {
        fprintf(stderr, "Error en la entrada de argumentos, revise los datos de entrada. \n Ejemplo de ejecución: ./exec/telefono [cola_Telefono] \n");
        exit(EXIT_FAILURE);
    }
    srand(pid);

    //TODO
    struct mq_attr attr;
    mqd_t qHandler;
    mqd_t qHandlerLines[NUMLINEAS];
    char buf[BUFSIZ];
    char BuzonLineas[S_MSG];
    sprintf(BuzonLineas, "%s", argv[1]);

    attr.mq_flags = 0;
    attr.mq_maxmsg = NUMLINEAS;
    attr.mq_sizemsg = S_MSG;
    attr.mq_curmsgs = 0;

    qHandler = mq_open(BuzonLlamadas, O_RDWR, &attr);
    if ( qHandler == -1 ) {
        perror("[TELEFONO] Error enla creacion de la cola de mensajes. \n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Telefono [%d] en espera ...  \n", pid);
        int entryMsg = mq_receive(qHadler, buf, S_MSG, NULL);
        if ( entryMsg==-1 ) {
            perror("[TELEFONO] Error al recibir mensaje de la cola de mensajes. \n");
            exit(EXIT_FAILURE);
        }
        printf("TELEFONO [%d] en conversacion de llamada desde Linea: /buzon_linea_%d \n", pid, BuzonLineas);
        sleep(rand() % 11 + 10);

        printf("TELEFONO [%d] ha colgado la llamada. %s \n", pid, BuzonLineas);
        if  ( mq_send(qHandlerLines, buf, strlen(BuzonLineas) + 1, 0) == -1 ) {
            perror("[TELEFONO] Error al enviar mensaje de fin a la linea");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}