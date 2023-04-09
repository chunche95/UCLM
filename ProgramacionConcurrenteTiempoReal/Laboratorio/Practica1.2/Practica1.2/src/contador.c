#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void contar(char* linea, char* num_linea);

int main(int argc, char* argv[])
{
    contar(argv[1], argv[2]);
    return EXIT_SUCCESS;
}

void contar(char* lineaA, char* numero_linea)
{
    int n_palabras = 0;
    int dentro_palabra = 0;
    const char *it = lineaA;

    do {
        if ((*it == '\0') || (*it == ' ') || (*it == '\t')
            || (*it == '\n') || (*it == '\r')) {
            if (dentro_palabra) {
                dentro_palabra = 0;
                n_palabras++;
            }
        }
        else {
            dentro_palabra = 1;
        }
    } while (*it++);

    printf(" Contador: %d", getpid());
    printf(" - La linea %d", (atoi(numero_linea)+ 1));
    printf(" tiene  %d", n_palabras );
    printf(" palabras.\n");
}