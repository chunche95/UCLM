#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <pthread.h>

#define MAX_TAMANYO 5

class Buffer {
    public:

        Buffer ();
        ~Buffer ();
        void anyadir (int dato);
        int extraer ();

    private:
        int _n_datos;
        int _primero, _ultimo;
        int _datos[MAX_TAMANYO];

        pthread_mutex_t _mutex;
        pthread_cond_t _buffer_no_lleno;
        pthread_cond_t _buffer_no_vacio;
};

#endif