
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <definitions.h>
#include <memoriaI.h>
#include <semaforoI.h>

/** 
 * Modulo principal
 * @param argc 
 * @param argv 
 * @return 
 */
int main(int argc,char *argv[]){

	//TODO: Esquema especificado en la práctica.
    // Variables globales
    pid_t pid = getpid();
    int tiempoEspera = obtener_var(LLAMADASESPERA);
    int n_waitTime = 0;
	//int sem_id, n_lines, pid, time_in_call;
    //struct sembuf sops;
    
    // Semaforos necesarios
    sem_t *linea = get_sem(LINEAS);
    sem_t *telefonos = get_sem(TELEFONOS);
    sem_t *mutex = get_sem(MUTEXESPERA);

    if (argc != 3) {
        printf("Usage: %s <n_lines> <time_in_call>\n", argv[0]);
        return 1;
    }	
    
    // Realiza una espera entre 1..60 segundos
    printf("Linea [%d] esperando llamada...\n",pid);
    sleep(rand() % 30 + 1);

    //Aumenta las llamadas en espera
    wait_sem(mutex);
    consultar_var(tiempoEspera, &n_waitTime);
    modificar_var(tiempoEspera, ++n_waitTime);

    // Espera telefono libre
    wait_sem(telefonos);
    printf("Linea [%d] esperando telefono libre...Nº Llamadas en espera: %d\n",pid,n_waitTime);

    // Lanza la llamada
    wait_sem(linea);
    printf("Linea [%d] desviando llamada a un telefono...\n",pid);
    signal_sem(linea);

    return EXIT_SUCCESS;
}