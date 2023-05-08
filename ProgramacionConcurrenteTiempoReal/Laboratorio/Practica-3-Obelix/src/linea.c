#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <mqueue.h>
#include <definitions.h>



// Generador de numeros aleatorios
int random_number(int min, int max) {
    return (rand() % ( max - min + 1 )) + min;
}

// Modulo principal del programa Obelix.
int main(int argc,char *argv[]){
    // Define variables locales
    int pid = getpid();
    // Declaramos buzones necesarios para el programa.
    mqd_t qHandlerLlamadas;
    mqd_t qHandlerLinea;
    char buzonLinea[TAMANO_MENSAJES];
    char buffer[TAMANO_MENSAJES+1];

    // Inicia Random
    srand(pid);

    // Verifica los parámetros
    if (argc != 2)
    {
        fprintf(stderr, "Error. Usa: ./exec/linea <cola_linea_llamante>.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buzonLinea,"%s",argv[1]);

    // generamos números random para los PIDs
    srand(pid);
    // Creamos los atributos de la cola de mensajes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = NUMLINES;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;
    // Creamos los buzones
    qHandlerLine = mq_open(BuzonLinea, O_RDWR, &attr);
    qHandlerCall = mq_open(BuzonLlamadas, O_WRONLY);

    // Creamos la cola de mensajes para notificar a los telefonos si hay un fallo al crear las colas de mensajes
    if  ( qHandlerLine == (mqd_t)-1) {
        perror("Error inesperado: Ha ocurrido un error al crear el buzon");
        exit(EXIT_FAILURE);
    }
    // Si todo ha ido bien, generamos un bucle infinito para esperar llamadas.
    while(1) {
        // Generamos el mensaje de espera y a su vez un random entre 1 y 10 seg
        printf("Linea [%d] esperando llamada...\n", pid);
        int waitTime = random_number(1, 10);
        sleep(waitTime);
        // Verificamos si hay una llamada en la cola de mensajes
        int entryMessage = mq_receive(qHandlerLine, buf, sizeof(MSG_SIZE+1), NULL);
        // Control de error al recibir
        if ( entryMessage == -1 ) { perror("Error inesperado: Error al recibir el mensaje."); exit(EXIT_FAILURE); }
        printf("Linea [%d] recibida llamada (/%s)...\n", pid, buzonLinea);
        printf("Linea [%d] esperando fin de conversacion...\n", pid);
        int sendMessage = mq_send(qHandlerCall, buf, strlen(buzonLinea)+1, 0);
        if ( sendMessage == -1 ) { perror("Error inesperado: Error al enviar el mensaje."); exit(EXIT_FAILURE); }
        // Esperamos alguna notificacion de los telefonos indicando en fin de alguna llamada
        int entryNewMessage  = mq_receive(qHandlerLine, buzonLinea ,sizeof(MSG_SIZE + 1), NULL);
        if ( entryNewMessage == -1 ) { perror("Error inesperado: Error al recibir el mensaje"); exit(EXIT_FAILURE); }
        printf("Linea [%d] conversación finalizada...\n",pid);
    }
    // Cerramos la cola de mensajes
    if ( mq_close(qHadlerLine) == -1 ) { perror("Ejecutado el cierre de la cola de mensajes: mq_close. \n"); exit(EXIT_FAILURE); }
    return EXIT_SUCCESS;
}
