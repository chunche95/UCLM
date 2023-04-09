#include <stdio.h>
#include <stdlib.h>
#include <lista.h>

int main(int argc, char *argv[])
{
  TLista *pLista;
  pLista = malloc(sizeof(TLista));
  crear(pLista, 7);
  longitud(pLista);

  insertar(pLista, 28);
  imprimir(pLista);
  longitud(pLista);
  
  insertarFinal(pLista, 27);
  imprimir(pLista);
  longitud(pLista);

  insertarN(pLista, 2, 7);
  imprimir(pLista);
  longitud(pLista);

  eliminar(pLista);
  imprimir(pLista);
  longitud(pLista);

  eliminarN(pLista, 3);
  imprimir(pLista);
  longitud(pLista);

  destruir(pLista);
  longitud(pLista);
  return 0;
}