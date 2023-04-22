#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <buffer.h>

#define NUM_HILOS 8

static void *productor_func (void *arg);
static void *consumidor_func (void *arg);

int main (int argc, char *argv[]){
    Buffer *buffer = new Buffer;
    pthread_t tids[NUM_HILOS];
    int i;
    srand((int) getpid());

    /*Creacion de hilos*/
    for (i=0;i < NUM_HILOS; i++)
        if((i%2) == 0)
            pthread_create(&tids[i], NULL, productor_func, buffer);
        else
            pthread_create(&tids[i], NULL, consumidor_func, buffer);

    /*Esperando a los hilos*/
    for(i=0; i< NUM_HILOS; i++)
        pthread_join(tids[i], NULL);

    delete buffer;

    return EXIT_SUCCESS;
}

static void *productor_func (void *arg){
    Buffer *buffer = (Buffer *) arg;
    int i = 0, valor;

    while (i<10){
        sleep(rand() % 3);
        valor = rand()%10;
        buffer->anyadir(valor);
        std::cout << "Productor:\t" << valor << std::endl;
        ++i;
    }

    return (void *) true;
}

static void *consumidor_func (void *arg){
    Buffer *buffer = (Buffer *) arg;
    int i = 0, valor;

    while (i<10){
        sleep(rand() % 5);
        valor = buffer->extraer();
        std::cout << "Consumidor:\t" << valor << std::endl;
        ++i;
    }

    return (void *) true;
}