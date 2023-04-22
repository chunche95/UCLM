#include <buffer.h>
#include <assert.h>

Buffer::Buffer(): _n_datos(0), _primero(0), _ultimo(0){
    pthread_mutex_init(&_mutex,NULL);
    pthread_cond_init(&_buffer_no_lleno, NULL);
    pthread_cond_init(&_buffer_no_vacio, NULL);
}

Buffer::~Buffer(){
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_buffer_no_lleno);
    pthread_cond_destroy(&_buffer_no_vacio);
}

void Buffer::anyadir(int dato){
    /*Adquisición del mutex para exclusión mutua*/
    pthread_mutex_lock(&_mutex);
        /*Controlar que no haya desbordamiento*/
        while(_n_datos==MAX_TAMANYO)
            pthread_cond_wait(&_buffer_no_lleno, &_mutex);

        /*Actualización del estado del buffer*/
        _datos[_ultimo % MAX_TAMANYO] = dato;
        ++_ultimo;
        ++_n_datos;

        /*Sincronización*/
        pthread_cond_signal(&_buffer_no_vacio);

    pthread_mutex_unlock(&_mutex);
}

int Buffer::extraer (){
    int dato;
    /*Adquisición del mutex para exclusión mutua*/
    pthread_mutex_lock(&_mutex);
    /*No se puede extraer si no hay nada*/
    while(_n_datos ==0)
        /*Sincronización*/
        pthread_cond_wait(&_buffer_no_vacio, &_mutex);

    /* Actualizacion del estado del buffer */
    dato = _datos[_primero % MAX_TAMANYO];
    ++_primero;
    --_n_datos;

    /* Sincronización */
        pthread_cond_signal(&_buffer_no_lleno);

    pthread_mutex_unlock(&_mutex);
    return dato;
}