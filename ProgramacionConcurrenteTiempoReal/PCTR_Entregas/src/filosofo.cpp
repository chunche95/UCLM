//
// Created by pauli on 09/04/2023.
//

#include "filosofo.h"
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TIME_PENSAR 7
#define MAX_TIME_COMER 5

void filosofo(char *filosofo, char *buzon_mesa,
              char *buzon_palillo_izq, char *buzon_palillo_der);

void controlador(int senhal);

int main(int argc, char *argv[]) {
    filosofo(argv[1], argv[2], argv[3], argv[4]);
    return 0;
}

void filosofo(char *filosofo, char *buzon_mesa,
              char *buzon_palillo_izq, char *buzon_palillo_der) {
    mqd_t qHandlerMesa, qHandlerIzq, qHandlerDer;
    int n_filosofo;
    char buffer[64];

    // Retrollamada de finalización.
    if (signal(SIGINT, controlador) == SIG_ERR) {
        fprintf(stderr, "Abrupt termination.\n");
        exit(EXIT_FAILURE);
    }
    n_filosofo = atoi(filosofo);

    // Recupera buzones.
    qHandlerMesa = mq_open(buzon_mesa, O_RDWR);
    qHandlerIzq = mq_open(buzon_palillo_izq, O_RDWR);
    qHandlerDer = mq_open(buzon_palillo_der, O_RDWR);

    srand((int) getpid());
    while (1) {
        printf("[Filosofo %d] pensando...\n", n_filosofo);
        sleep(rand() % MAX_TIME_PENSAR); // Pensar.

        mq_receive(qHandlerMesa, buffer, sizeof(buffer), NULL);

        // Hambriento (coger palillos)...
        mq_receive(qHandlerIzq, buffer, sizeof(buffer), NULL);
        mq_receive(qHandlerDer, buffer, sizeof(buffer), NULL);
        // Comiendo...
        printf("[Filosofo %d] comiendo...\n", n_filosofo);
        sleep(rand() % MAX_TIME_COMER); // Comer.
        // Dejar palillos...
        mq_send(qHandlerIzq, buffer, sizeof(buffer), 0);
        mq_send(qHandlerDer, buffer, sizeof(buffer), 0);

        mq_send(qHandlerMesa, buffer, sizeof(buffer), 0);
    }
}

id controlador(int senhal) {
    printf("[Filosofo %d] Finalizado (SIGINT)\n", getpid());
    exit(EXIT_SUCCESS);
}
