//
// Created by pauli on 09/04/2023.
//

#include "manager.h"

#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define BUZON_MESA "/buzon_mesa"
#define BUZON_PALILLO "/buzon_palillo_" /* Offset! */
#define FILOSOFOS 5

pid_t pids[FILOSOFOS];
mqd_t qHandlerMesa;
mqd_t qHandlerPalillos[FILOSOFOS];

void controlador(int senhal);
void liberarecursos();
void finalizarprocesos();

int main(int argc, char *argv[]) {
    int i;
    struct mq_attr mqAttr;
    char buffer[64], caux[30], filosofo[1];
    char buzon_palillo_izq[30], buzon_palillo_der[30];

// Reseteo del vector de pids.
    memset(pids, 0, sizeof(pid_t) * (FILOSOFOS));

// Atributos del buzón mesa.
    mqAttr.mq_maxmsg = (FILOSOFOS - 1);
    mqAttr.mq_msgsize = 64;

// Retrollamada de finalización.
    if (signal(SIGINT, controlador) == SIG_ERR) {
        fprintf(stderr, "Abrupt termination.\n");
        exit(EXIT_FAILURE);
    }

// Creación de buzones...
    qHandlerMesa = mq_open(BUZON_MESA, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR, &mqAttr);
    for (i = 0; i < (FILOSOFOS - 1); i++)
        // Para evitar el interbloqueo...
// Sólo 4 filósofos (máximo) intentan acceder a los palillos.
        mq_send(qHandlerMesa, buffer, sizeof(buffer), 1);

// Para los buzones de los palillos.
    mqAttr.mq_maxmsg = 1;

// Un buzón por palillo...
    for (i = 0; i < FILOSOFOS; i++) {
        sprintf(caux, " %s %d", BUZON_PALILLO, i);
        qHandlerPalillos[i] = mq_open(caux, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR, &mqAttr);
        // Palillo inicialmente libre.
        mq_send(qHandlerPalillos[i], buffer, sizeof(buffer), 0);
    }

// Lanzamiento de procesos filósofo.
    for (i = 0; i < FILOSOFOS; i++)
        if ((pids[i] = fork()) == 0) {
            sprintf(filosofo, " %d", i);
            sprintf(buzon_palillo_izq, " %s %d", BUZON_PALILLO, i);
            sprintf(buzon_palillo_der, " %s %d", BUZON_PALILLO, (i + 1) % FILOSOFOS);
            execl("./exec/filosofo", "filosofo", filosofo, BUZON_MESA,buzon_palillo_izq, buzon_palillo_der, NULL);
        }

    for (i = 0; i < FILOSOFOS; i++) waitpid(pids[i], 0, 0);
    finalizarprocesos();
    liberarecursos();
    printf("\n Fin del programa\n");
    return 0;
}

void controlador(int senhal) {
    finalizarprocesos();
    liberarecursos();
    printf("\n Fin del programa (Control + C)\n");
    exit(EXIT_SUCCESS);
}

void liberarecursos() {
    int i;
    char caux[30];
    printf("\n Liberando buzones... \n");
    mq_close(qHandlerMesa);
    mq_unlink(BUZON_MESA);

    for (i = 0; i < FILOSOFOS; i++) {
        sprintf(caux, " %s %d", BUZON_PALILLO, i);
        mq_close(qHandlerPalillos[i]);
        mq_unlink(caux);
    }
}

void finalizarprocesos() {
    int i;
    printf("-------------- Terminando ------------- \n");
    for (i = 0; i < FILOSOFOS; i++) {
        if (pids[i]) {
            printf("Finalizando proceso [ %d]... ", pids[i]);
            kill(pids[i], SIGINT);
            printf("<Ok>\n");
        }
    }
}