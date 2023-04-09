#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_BUFFER 500

void comprobarParecidos(char* nombreFichero, char* patron) {
    FILE* fd;
    int numeroLineas = 1;
    char buffer[MAX_BUFFER];
    char texto[MAX_BUFFER];
    if ((fd = fopen(nombreFichero, "r")) == NULL) {
        printf(" Error: Fallo en la apertura del archivo. \n");
    }
    else {
        while (fget(buffer, MAX_BUFFER, fd)) {
            strcat(texto, buffer);
        }
        fclose(fd);

        const char* pPatron = patron;
        char caracter = pPatron[0];
        int sizePatron = strlen(pPatron);
        int sizeText = strlen(texto);
        int i = 0;

        while (i < sizeText) {
            if (texto[i] == '\n')
            {
                ++numeroLineas;
            }
            if (texto[i] == caracter) {
                if (strncmp(&texto[i], pPatron, sizePatron) == 0) {
                    printf(" Procesador: " + getpid() + " Patron: " + pPatron + " encontrado en la linea " + numeroLineas + " \n");
                }
            }
            i++;
        }
    }
}

int main(int argc, char* argv[]) {
    comprobarParecidos(argv[1], argv[2]);
    return EXIT_SUCCESS;
}