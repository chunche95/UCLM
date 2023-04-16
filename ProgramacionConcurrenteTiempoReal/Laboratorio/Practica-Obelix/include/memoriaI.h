
#ifndef __VARIABLEI_H__
#define __VARIABLEI_H__


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

// Crea un objeto de memoria compartida.
// Devuelve el descriptor de archivo.
int crear_var(const char *name, int valor);

// Obtiene el descriptor asociado a la variable.
int obtener_var(const char *name);

// Destruye el objeto de memoria compartida.
void destruir_var(const char *name);

// Modifica el valor del objeto de memoria compartida.
void modificar_var(int shm_fd, int valor);

// Consulta el valor del objeto de memoria compartida.
void consultar_var(int shm_fd, int *valor);

#endif
