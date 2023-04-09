#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_BUFFER 500

void comprobarParecidos(char* nombreFichero, char* patron) {
    FILE* fichero;
    int numeroLineas = 1;
    char buffer[MAX_BUFFER];
    char texto[MAX_BUFFER];
    if ((fichero = fopen(nombreFichero, "r")) == NULL) {
        printf(" Error: Falloal abrir el archivo. \n");
    } else {
        while (fgets(buffer, MAX_BUFFER, fichero)) {
            strcat(texto, buffer);
        }
        fclose(fichero);

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
                    printf(" Procesador: %d Patron '%s' en la linea ",getpid(), pPatron);
                    printf("%d\n",numeroLineas);
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
