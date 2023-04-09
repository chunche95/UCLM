#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TNodo *buscarNodoAnterior(TLista *lista, int index);
TNodo *buscarUltimoNodo(TLista *lista);
// Crea una lista con un nodo.
void crear(TLista *pLista, char valor[])
{
    pLista->pPrimero = malloc(sizeof(TNodo));
    strcpy(pLista->pPrimero->valor, valor);
    pLista->pPrimero->pSiguiente = NULL;
}

void destruir(TLista* pLista)
{
    TNodo* pAux1;
    struct Nodo* pAux2;

    for (pAux1 = pLista->pPrimero; pAux1 != NULL;)
    {
        pAux2 = pAux1->pSiguiente;
        free(pAux1);
        pAux1 = pAux2;
    }

    free(pLista);
}

/**
 * Funcion INSERTAR.
 *
 * Primero se crea un nuevo nodo con el valor proporcionando y se establece su campo 'pSiguiente' a NULL.
 * Luego, si la lista enlazada est� vac�a, el nuevo nodo se convierte en el primer nodo de la lista.
 * De lo contrario, se recorre la lista hasta el �ltimo nodo y se establece el campo 'pSiguiente' del �ltimo nodo en el nuevo nodo,
 * convirti�ndolo en el nuevo �ltimo nodo de la lista.
*/
void insertar(TLista* pLista, char valor[])
{
    TNodo* nuevo_nodo = malloc(sizeof(TNodo));
    strcpy(nuevo_nodo->valor, valor);
    nuevo_nodo->pSiguiente = NULL;

    if (pLista->pPrimero == NULL) {
        pLista->pPrimero = nuevo_nodo;
    }
    else {
        TNodo* nodo_actual = pLista->pPrimero;
        while (nodo_actual->pSiguiente != NULL) {
            nodo_actual = nodo_actual->pSiguiente;
        }
        nodo_actual->pSiguiente = nuevo_nodo;
    }
}

/**
* Funcion INSERTARFINAL.
*
* Crea un nuevo nodo con el valor pasapor por parametro y se establece pSiguiente a null. Luego, se llama a una funcion que llamaremos 'buscarUltimoNodo'
* para obtener el �ltimo nodo de la lista enlazada.
* Si la lista esta vacia, el nuevo nodo se convierte en el primer nodo de la lista, en caso contrario, pSiguiente  es el �ltimo nodo en el nuevo nodo creado.
*/
void insertarFinal(TLista* pLista, char valor[])
{
    TNodo* nuevo_nodo = malloc(sizeof(TNodo));
    strcpy(nuevo_nodo->valor, valor);
    nuevo_nodo->pSiguiente = NULL;
    TNodo* ultimo_nodo = buscarUltimoNodo(pLista);
    if (pLista->pPrimero == NULL) {
        pLista->pPrimero = nuevo_nodo;
    }
    else {
        ultimo_nodo->pSiguiente = nuevo_nodo;
    }
}

/**
* Funcion BUSCARULTIMONODO.
*
* Recorre la lista enlazada hasta encontrar el �ltimo nodo y lo devuelve, @returnnodo_actual,  como resultado,
* Si la lista esta vacia devuelve NULL, en caso contrario, devuelve el valor encontrado en pLista.
*/
TNodo* buscarUltimoNodo(TLista* pLista) {
    if (pLista->pPrimero == NULL) {
        return NULL;
    }
    else {
        TNodo* nodo_actual = pLista->pPrimero;
        while (nodo_actual->pSiguiente != NULL) {
            nodo_actual = nodo_actual->pSiguiente;
        }
        return nodo_actual;
    }
}

// Suponemos n = 1, 2, ...
/**
* Funcion INSERTARN.
*
* Creamos un nuevo nodo con el valor enviado por parametro y se establece su campo 'pSiguiente' a NULL.
* - Si el �ndice es cero el nuevo nodo se convierte en el primer nodo de la lista, en caso contrario, busca el nodo anterior al �ndice especifico
* usando la funcion @see BuscarNodoAnterior.
* - Si el �ndice est� fuera de rango se muestra un error sin hacer cambios en la lista.
* - Si hay huecos libres en la lista, se establece el campo pSiguiente del nuevo nodo en el nodo siguiente al nodo anterior encontrado y ponemos el campo pSiguiente
* del nodo anterior en el nuevo nodo, insertamos el nuevo nodo en la lista en la posici�n espec�fica.
*/
void insertarN(TLista* pLista, int index, char valor [])
{
    TNodo* nuevo_nodo = malloc(sizeof(TNodo));
    strcpy(nuevo_nodo->valor, valor);
    nuevo_nodo->pSiguiente = NULL;

    if (index == 0) {
        nuevo_nodo->pSiguiente = pLista->pPrimero;
        pLista->pPrimero = nuevo_nodo;
    }
    else {
        TNodo* nodo_anterior = buscarNodoAnterior(pLista, index);
        if (nodo_anterior == NULL) {
            printf("Indice fuera de rango.\n");
            return;
        }
        nuevo_nodo->pSiguiente = nodo_anterior->pSiguiente;
        nodo_anterior->pSiguiente = nuevo_nodo;
    }
}

/**
* Funcion BUSCARNODOANTERIOR.
*
* Recorre la lista enlazada hasta encontrar el nodo anterior al �ndice espec�ficado y lo devuelve @retrun nodo_actual, como resultado. Si el �ndice est� fuera de rango se da un NULL.
*/
TNodo* buscarNodoAnterior(TLista* pLista, int index) {
    if (pLista->pPrimero == NULL) {
        return NULL;
    }
    else {
        TNodo* nodo_actual = pLista->pPrimero;
        int i = 0;
        while (nodo_actual->pSiguiente != NULL && i < index - 1) {
            nodo_actual = nodo_actual->pSiguiente;
            i++;
        }
        if (i < index - 1) {
            return NULL;
        }
        return nodo_actual;
    }
}

// Elimina el primer elemento de la lista.
/**
* Funcion ELIMINAR.
*
* Verifica si la lista est� vac�a.
* - Lo est�: La funci�n indica un mensake de error y no devuelve ning�n cambio @return
* - No lo est�: Se asigna el campo pPrimero de la lista en el nodo siguiente al primer nodo actual, y luego, se libera el primer nodo actual usando la funci�n free.
* Eliminando el primer nodo de la lista
*/
void eliminar(TLista* pLista)
{
    if (pLista->pPrimero == NULL) {
        printf("La lista est� vac�a.\n");
    }
    else {
        TNodo* nodo_a_eliminar = pLista->pPrimero;
        pLista->pPrimero = pLista->pPrimero->pSiguiente;
        free(nodo_a_eliminar);
    }
}

/**
* Funcion ELIMINARN.
*
* Se comprueba el estado de la lista:
* - Esta vacia: Muestra un mensaje de que est� vacia
* - No esta vac�a:
*   - Si el �ndice marcado es 0, usa la misma l�gica que la funci�n @see eliminar.
*   - Si el �ndice es distinto de 0, busca el nodo anterior al �ndice especificado usando la funcion @see buscarNodoAnterior
*   y 'pSiguiente' del nodo aanterior en el nodo siguiente al nodo a eliminar y se libera el nodo a eliminar usando 'free', liberando la posici�n especificada de la lista.
*   - Si el indice est� fuera de rango, mostramos un mensaje de error
*/
void eliminarN(TLista* pLista, int index)
{
    if (pLista->pPrimero == NULL) {
        printf("La lista est� vac�a.\n");
        return;
    }
    else if (index == 0) {
        TNodo* nodo_a_eliminar = pLista->pPrimero;
        pLista->pPrimero = pLista->pPrimero->pSiguiente;
        free(nodo_a_eliminar);
    }
    else {
        TNodo* nodo_anterior = buscarNodoAnterior(pLista, index);
        if (nodo_anterior == NULL || nodo_anterior->pSiguiente == NULL) {
            printf("Indice fuera de rango.\n");
            return;
        }
        TNodo* nodo_a_eliminar = nodo_anterior->pSiguiente;
        nodo_anterior->pSiguiente = nodo_anterior->pSiguiente->pSiguiente;
        free(nodo_a_eliminar);
    }
}

/**
* Funcion GETELEMENTON.
*
* Verifica  si la lista est� vacia, si lo est�, lo indica y devuelve 0. En caso contrario, se recorre la lista usando un bucle comparando el �ndice actual
* del nodo indicado por parametro 'index', si coinciden dichos indices la funci�n devuelve el valor del nodo actual.
* Si no lo encuentra, la funci�n muestra un mensaje de error y devuelve @return -1.
*/
const char* getElementoN(TLista* pLista, int index)
{
    if (pLista->pPrimero == NULL) {
        printf("La lista est� vac�a.\n");
        return 0;
    }
    else {
        TNodo* nodo_actual = pLista->pPrimero;
        int contador = 0;
        while (nodo_actual != NULL) {
            if (contador == index) {
                return nodo_actual->valor;
            }
            nodo_actual = nodo_actual->pSiguiente;
            contador++;
        }
        printf("Indice no encontrado en la lista.\n");
        return NULL;
    }
}

/**
* Funcion IMPRIMIR.
*
* Comprobamos que la lista enviada por par�metro 'pLista' no est� vacia, si lo est� lo indicamos con un mensaje de error.
* En caso de tener elementos, se imprimen los valores encontrados gracias a un bucle y avanzamos al siguiente nodo de la lista.
*/
void imprimir(TLista* pLista)
{
    if (pLista->pPrimero == NULL) {
        printf("La lista est� vac�a.\n");
    }
    else {
        TNodo* nodo_actual = pLista->pPrimero;
        while (nodo_actual != NULL) {
            printf("%s\n",nodo_actual->valor);
            nodo_actual = nodo_actual->pSiguiente;
        }
        printf("\n");
    }
}

/**
* Funci�n LONGITUD.
*
* Inicializa un contador a 0 que devolveremos como resultado @return contador.
*
* Creamos un puntero al primer nodo de la lista, luego, se recorre la llista usando un bucle, en cada iteraci�n, se incrementa el contador y se avanza al siguiente nodo en la lista.
* Despues de recorrer todos los elementos, se devuelve la longitud encontrada.
*/
int longitud(TLista* pLista)
{
    int contador = 0;
    TNodo* nodo_actual = pLista->pPrimero;
    while (nodo_actual != NULL) {
        contador++;
        nodo_actual = nodo_actual->pSiguiente;
    }
    return contador;
}