//
// Created by pauli on 09/04/2023.
//
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int filosofos = 5, palillos = 5;
int randomActualFilosofo = 0, randomActualPalillo = 0;
int posicionFilosofos[] = {1,2,3,4,5};
int posicionPalillos[] = {1,2,3,4,5};

int ranFilosofo1, ranFilosofo2, tiempo = 3;
int tenedores[] = {0,0,0,0,0,0};
int tenOcupados[] = {0,0,0,0,0,0};

// Asignamos posiciones de los filosofos y los palillos
void asignaPosiciones() {
    for (int i = 1; i <= 5 ; i++) {
        posicionFilosofos[i] = i;
        posicionPalillos[i] = i;
    }
}

// Generamos un numero aleatorio del 1 al 5
int generaNumeroAleatorio() {
    int nAleatorio = rand() % 5 +1;
    return nAleatorio;
}

// Imprime las posiciones
void imprimePosiciones() {
    // Imprime las posiciones de los palillos
    for (int i = 1; i <= 5; i++) {
        cout << i << ") Posicion palillos: " << posicionPalillos[i] << " Posicion filosofo: " << posicionFilosofos[i] << " \n";
    }
}

void comer(int ten1, int ten2, int posiFilosofo ) {
    cout << " \n Filosofo meditando ... \n";
    if  ( tenOcupados[ten1] != 0 ) {
        sleep(tiempo);
        cout << "\n Palillo: " << ten1 << " Ocupado!  El filósofo no puede comer: " << posiFilosofo << " Proceso morirá por inanicion \n";
    } else {
        sleep(tiempo);
        tenOcupados[ten1] = posiFilosofo;
        cout << "\n El filosofo: " << posiFilosofo << " esta cominedo con el palillo: " << ten2;
    }
}

void jugar(int filosofo) {
    cout << "\n Filosofo: " << filosofo;
    if ( posicionFilosofos[filosofo] == 1 ) {
        cout << "\n Come \n";
        comer(1,5,1);
    } else if ( posicionFilosofos[filosofo] == 2 ) {
        cout << "\n Come \n";
        comer(1,2,2);
    } else if ( posicionFilosofos[filosofo] == 3 ) {
        cout << "\n Come \n";
        comer(2,3,3);
    } else if ( posicionFilosofos[filosofo] == 4 ) {
        cout << "\n Come \n";
        comer(3,4,4);
    } else if ( posicionFilosofos[filosofo] == 5 ) {
        cout << "\n Come \n";
        comer(4,5,5);
    }
}
void generarFilosofos() {
    srand (time(NULL));
    srand ((unsigned)time(0));
    while (ranFilosofo1 == 0) {
        ranFilosofo1 = generaNumeroAleatorio();
    }
    ranFilosofo2 = generaNumeroAleatorio();
    while ( ranFilosofo2 == ranFilosofo1 ) {
        if ( ranFilosofo2 == 0 ) {
            ranFilosofo2 = generaNumeroAleatorio();
        }
        ranFilosofo2 = generaNumeroAleatorio();
    }
    cout << ranFilosofo1 << "-" << ranFilosofo2 << "\n";
    jugar(ranFilosofo1);
    jugar(ranFilosofo2);
}
int main() {
    srand((unsigned)time(0));
    imprimePosiciones();
    cout<<"\n Ingrese cantidad de jugadas: \n";
    int total;
    cin >> total;
    for (int i = 0; i < total; ++i) { // ------------------------ VER POSICION COMO LAS IMPRIME
        cout <<"--------------------------------------------------\n";
        cout <<"| ------ + -- JUGADA " << i << " -- + ---------  |\n";
        cout <<"--------------------------------------------------\n";
        for (int j = 0; j <= 5; ++j) { // SAME QUE EL OTRO BUCLE
            tenOcupados[j] = 0;
        }
        ranFilosofo1 = rand() % 5 + 1;
        ranFilosofo2 = rand() % 5 + 1;
        generarFilosofos();
        sleep(tiempo);
    }
}