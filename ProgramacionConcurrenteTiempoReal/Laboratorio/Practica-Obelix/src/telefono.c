
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <definitions.h>
#include <memoriaI.h>
#include <semaforoI.h>

// Modulo principal
int main(int argc,char *argv[]){


	//TODO: Esquema según especificado en la práctica.

    // Define variables locales

    pid_t pid = getpid();
    int valorEspera = obtener_var(LLAMADASESPERA);
    int i = 0;

    sem_t *mutex = get_sem(MUTEXESPERA);
    sem_t *linea_lista = get_sem(LINEAS);
    sem_t *telefonos_libres = get_sem(TELEFONOS);

    
    // Se pone en estado de libre incrementando el número de teléfonos libres
    while(1){

        // Mensaje de Espera
        printf("Teléfono [%d] en espera...\n",pid);
        
        //Llamadas en espera
		signal_sem(telefonos_libres);
        wait_sem(linea_lista);

        //Decremento del llamadas en espera
        wait_sem(mutex);
        consultar_var(valorEspera, &i);
        modificar_var(valorEspera, --i);

        // Mensaje de en conversacion
        signal_sem(mutex);
        printf("Teléfono [%d] en conversacion... Nº Llamadas en espera: %d\n",pid,valorEspera);

        // Espera en conversación
        sleep(rand() % 10 + 10);
        
    }

    return EXIT_SUCCESS;
}