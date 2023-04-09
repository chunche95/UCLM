#include <stdio.h>

typedef struct Nodo {
	char valor[500];
	struct Nodo* pSiguiente;
} TNodo;
typedef struct {
	TNodo* pPrimero;
} TLista;


void crear (TLista* pLista, char valor []);
void destruir (TLista* pLista);
// 'insertar' inserta al ppio de la lista.
void insertar (TLista* pLista, char valor []) ;
void insertarFinal (TLista* pLista, char valor []);
void insertarN (TLista* pLista, int index, char valor []);
// 'elimina' elimina el último de la lista.
void eliminar (TLista* pLista);
void eliminarN (TLista* pLista, int index);
const char* getElementoN (TLista* pLista, int index);
void imprimir (TLista* pLista);
int longitud(TLista *pLista);


