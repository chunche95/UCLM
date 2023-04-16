#include <errno.h>
#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <definitions.h>
#include <memoriaI.h>
#include <semaforoI.h>

void procesar_argumentos(int argc, char *argv[], int *numTelefonos, int *numLineas);
void instalar_manejador_senhal();
void manejador_senhal(int sign);
void iniciar_tabla_procesos(int n_procesos_telefono, int n_procesos_linea);
void crear_procesos(int numTelefonos, int numLineas);
void lanzar_proceso_telefono(const int indice_tabla);
void lanzar_proceso_linea(const int indice_tabla);
void esperar_procesos();
void terminar_procesos(void);
void terminar_procesos_especificos(struct TProcess_t *process_table, int process_num);
void liberar_recursos();

/**
 * Variables globales
 */
int g_telefonosProcesses = 3; // Valores iniciales por defecto
int g_lineasProcesses = 10;
struct TProcess_t *g_process_telefonos_table;
struct TProcess_t *g_process_lineas_table;


int main(int argc, char *argv[])
{
    // Define variables locales
    int numTelefonos = 3;
    int numLineas = 10;

    // Procesa los argumentos y los guarda en las dos variables
    procesar_argumentos(argc,argv,&numTelefonos,&numLineas);

    // Creamos semáforos de espera y para los telefonos y memoria compartida
    crear_sem(MUTEXESPERA,1); crear_sem(TELEFONOS,0);crear_sem(LINEAS,0);
    crear_var(LLAMADASESPERA,0);  // No hay llamadas en espera

    // Manejador de Ctrl-C
    instalar_manejador_senhal();
 
    // Crea Tabla para almacenar los pids de los procesos
    iniciar_tabla_procesos(numTelefonos, numLineas);

    // Tenemos todo
    // Lanzamos los procesos
    crear_procesos(numTelefonos,numLineas);
  
    // Esperamos a que finalicen las lineas
    esperar_procesos();

    // Matamos los telefonos y cualquier otro proceso restante
    terminar_procesos();

    // Finalizamos Manager
    printf("\n[MANAGER] Terminacion del programa (todos los procesos terminados).\n");
    liberar_recursos();

    return EXIT_SUCCESS;
}

/**
 * Procesamiento de los argumentos pasaados por argc y argv
 * @param argc
 * @param argv
 * @param numTelefonos
 * @param numLineas
 */
void procesar_argumentos(int argc, char *argv[], int *numTelefonos, int *numLineas) {
    if (argc != 3)
    {
        printf("\t Uso: exec/manager <num_telefonos> <num_lineas> \n");
        exit(EXIT_FAILURE);
    }
    *numTelefonos = atoi(argv[1]);
    *numLineas = atoi(argv[2]);
    
}
/**
 *  Instala el controlador de señal
 */
void instalar_manejador_senhal() {
    if (signal(SIGINT, manejador_senhal) == SIG_ERR) {
        fprintf(stderr, "[MANAGER] Error al instalar el controlador de sennal. %s. \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

/**
 * Control de la señal de emergencia del programa.
 * Ctrl + C
 * @param sign
 */
void manejador_senhal(int sign) {
    printf("\n[MANAGER] Terminacion de emergencia del programa (Ctrl-C).\n");

    // Finalizamos las lineas y telefonocres
    terminar_procesos_especificos(g_process_lineas_table, g_lineasProcesses);
    terminar_procesos_especificos(g_process_telefonos_table, g_telefonosProcesses);
    // Liberación de los recursos usados
    liberar_recursos();
    exit(EXIT_SUCCESS);
}

/**
 * Inicializador de la tabla de procesos de telefono y lineas.
 * @param n_procesos_telefono
 * @param n_procesos_linea
 */
void iniciar_tabla_procesos(int n_procesos_telefono, int n_procesos_linea) {
    // Calculamos el tamaño de la tabla de procesos para los telefonos y las lienas
    int tabla_telef_size = sizeof(struct TProcess_t) *n_procesos_telefono;
    int talbla_lineas_size = sizeof(struct TProcess_t) *n_procesos_linea;
    // Reservamos memoria para ambas tablas
    g_process_telefonos_table = malloc(tabla_telef_size);
    g_process_lineas_table = malloc(talbla_lineas_size);
    // Bucle que inicializa los valores de las tablas
    for (int i = 0; i < n_procesos_telefono; i++)
    {
        g_process_telefonos_table[i].pid = -1;
        // g_process_telefonos_table[i].status = PROCESS_STATUS_UNUSED;
    }
    for (int i = 0; i < n_procesos_linea; i++)  
    {
        g_process_lineas_table[i].pid = -1;
        // g_process_lineas_table[i].status = PROCESS_STATUS_UNUSED;
    }
    // Actualizamos las variables globales
    g_telefonosProcesses = n_procesos_telefono;
    g_lineasProcesses = n_procesos_linea;

}

/**
 * Creacion de los procesos necesarios para la realización de las llamadas con las lineas de telefono y los telefonos existentes.
 * @param numTelefonos
 * @param numLineas
 */
void crear_procesos(int numTelefonos, int numLineas) {
     int i;
    // Lanza los procesos de telefonos
    printf("[MANAGER] %d telefonos creados. \n" , numTelefonos);
    for (i = 0; i < numTelefonos; i++) {
        lanzar_proceso_telefono(i);
    }
    printf("[MANAGER] %d lineas creadas. \n", numLineas);
    // Lanza los procesos de lineas
    for (i = 0; i < numLineas; i++) {
        lanzar_proceso_linea(i);
    }
}

/**
 * Metodo encargado de la creación de los indices de las tablas de procesos para telefono
 * @param indice_tabla
 */
void lanzar_proceso_telefono(const int indice_tabla) {
    pid_t pid = fork();

    if (pid < 0) {
        // Fallo de la creación del proceso
        printf("[MANAGER] Error al crear proceso telefono %d\n", indice_tabla);
        terminar_procesos();
        liberar_recursos();
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Es el proceso hijo
        execl("./telefono", "./telefono", NULL);
        printf("[MANAGER] Error al ejecutar proceso telefono %d\n", indice_tabla);
        exit(EXIT_FAILURE);
    } else {
        // Es el proceso padre
        g_process_telefonos_table[indice_tabla].pid = pid;
        g_process_telefonos_table[indice_tabla].clase = CLASE_TELEFONO;
        // g_process_telefonos_table[indice_tabla].active = 1;
        g_telefonosProcesses++;
    }
}

/**
 * Metodo encargado de la creación de los índices de las tablas de procesos para lineas
 * @param indice_tabla
 */
void lanzar_proceso_linea(const int indice_tabla) {
    pid_t pid = fork();
    if (pid < 0) {
        printf("[MANAGER] Error al crear proceso linea %d\n", indice_tabla);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Es el proceso hijo
        execl("./linea", "./linea", NULL);
        printf("[MANAGER] Error al ejecutar proceso linea %d\n", indice_tabla);
        exit(EXIT_FAILURE);
    } else {
        // Es el proceso padre
        g_process_lineas_table[indice_tabla].pid = pid;
        g_process_lineas_table[indice_tabla].clase = CLASE_LINEA;
        //g_process_lineas_table[indice_tabla].active = 1;
        g_lineasProcesses++;
    }
}

/**
 * Metodo de ejecución del tiempo de  espera del programa.
 */
void esperar_procesos() {
    pid_t pid;
    int n_process = g_lineasProcesses;

    while (n_process > 0)
    {
        pid = wait(NULL);
        for (int i = 0; i < n_process; ++i) {
            if ( pid == g_process_lineas_table[i].pid) {
                printf("[MANAGER] Proceso de linea terminado \t [%d] \n", g_process_lineas_table[i].pid);
                g_process_lineas_table[i].pid = 0;
                n_process--;
                break;
            }
        }
    }
    for (int i = 0; i < g_telefonosProcesses; ++i) {
        terminar_procesos_especificos(&g_process_telefonos_table[i], 0);
    }
}

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!!!!!! PTE DE REVISAR BUCLE DE FIN !!!!!!!!!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
/**
 * Terminar procesos del programa tanto de linea como de telefonos generados
 */
void terminar_procesos(void) {
    // Envio de la señal SIGTERM a todos los procesos de grupo de procesos actuales
    int i=0, j=0;
    printf ("\n \t Finalizando procesos \n");
    // Finalización de procesos lineas
    while (i < g_lineasProcesses ) {
        if ( g_process_lineas_table[i].pid != 0) {
            printf("[MANAGER] Terminando procesos %s \t [%d] \n", g_process_lineas_table[i].clase, g_process_lineas_table[i].pid);
            if ( kill(g_process_lineas_table[i].pid, SIGINT) == -1) {
                fprintf(stderr,"[MANAGER] Error al ejecutar señal KILL() en el proceso %d: %s \n", g_process_lineas_table[i].pid,strerror(errno));
            }
        }
        i++;
    }
    // Finalización de procesos telefonos
    while (j < g_telefonosProcesses ) {
        if ( g_process_telefonos_table[i].pid != 0) {
            printf("[MANAGER] Terminando procesos %s \t [%d] \n", g_process_telefonos_table[i].clase, g_process_lineas_table[i].pid);
            if ( kill(g_process_telefonos_table[i].pid, SIGINT) == -1) {
                fprintf(stderr,"[MANAGER] Error al ejecutar señal KILL() en el proceso %d: %s \n", g_process_lineas_table[i].pid,strerror(errno));
            }
        }
        j++;
    }
}

/**
 * Metodo que finaliza un proceso en particular, necesita como parametros.
 * @param process_table
 * @param process_num
 */
void terminar_procesos_especificos(struct TProcess_t *process_table, int process_num) {
    printf("\n[MANAGER] Terminando proceso %s [%d] ...  \n", process_table[process_num].clase, process_table[process_num].pid);
    if (kill(g_process_telefonos_table[process_num].pid, SIGINT) == -1 ) {
        fprintf(stderr, "\n[MANAGER] Error al matar el proceso %d: %s.\n", process_table[process_num].pid, strerror(errno));
    }
}
void liberar_recursos() {
    free(g_process_telefonos_table);
    free(g_process_lineas_table);
}