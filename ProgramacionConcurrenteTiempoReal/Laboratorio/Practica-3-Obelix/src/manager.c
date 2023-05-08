#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include <mqueue.h>
#include <definitions.h>

void crear_buzones();
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

int g_telefonosProcesses = 0;
int g_lineasProcesses = 0;
struct TProcess_t *g_process_telefonos_table;
struct TProcess_t *g_process_lineas_table;
mqd_t qHandlerLlamadas;
mqd_t qHandlerLineas[NUMLINEAS];


int main(int argc, char *argv[])
{
    // Controlamos la entrada de argumentos del programa
    if ( argc != 3 ) {
        printf("-------------------------------------");
        printf("--------------- Error ---------------");
        printf("-------------------------------------");
        printf("La entrada de argumentos es incorrecta.\n");
        printf("Revise la entrada y vuelva a intentarlo de nuevo. \n\n");
        printf("Ejemplo de ejecucion:\n");
        printf("./exec/manager [n_telefonos] [n_lineas] \n");
    }
    // Define variables locales

    // Creamos los buzones
    crear_buzones();

    // Manejador de Ctrl-C
    instalar_manejador_senhal();
 
    // Crea Tabla para almacenar los pids de los procesos
    iniciar_tabla_procesos(NUMTELEFONOS,NUMLINEAS);

    // Tenemos todo
    // Lanzamos los procesos
    crear_procesos(NUMTELEFONOS,NUMLINEAS);
  
    // Esperamos a que finalicen las lineas
    esperar_procesos();

    // Matamos los telefonos y cualquier otro proceso restante
    terminar_procesos();


    // Finalizamos Manager
    printf("\n[MANAGER] Terminacion del programa (todos los procesos terminados).\n");
    liberar_recursos();

    return EXIT_SUCCESS;
}

//TODO

void crear_buzones(){
    // Buzon de llamadas
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = N_LINES;
    attr.mq_msgsize = M_SIZE;
    attr.mq_curmsgs = 0;

    /*
     * Con mq_open, generamos una cola de mensajes con los siguientes atributos:
     * - BuzonLlamadas: Cola de mensaje definida en definitions.h
     * - O_CREAT | O_RDW: Banderas de creación, lectura y escritura
     * - S_IRUSR | S_IWUSR: Permisos que damos a la cola de mensajes - Lectura y escritura.
     * - &attr: Puntero con los atributos definidos para la cola de mensajes
     */
    qHandlerLlamadas = mq_open(BuzonLlamadas, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    if ( qHalderLlamadas == ( mqd_t ) - 1 ) {
        perror (" Error inesperado: \n Error al crear la cola de mensajes para llamadas. \n");
        exit(EXIT_FAILURE);
    }
    // Buzon de lineas
    char BuzonLinea[M_SIZE];
    for ( int i = 0; i < N_LINES; i++ ) {
        sprintf(BuzonLinea, "%s%d", BUZON_LINEAS, i);
        qHandlerLineas[i] = mq_open(BuzonLinea | O_RDWR, S_IRUSR | S_IWUSR, &attr);
        if ( qHandlerLineas[i] == (mqd_t) - 1 ) {
            perror( " Error inesperado: \n Error al crear la cola de mensajes para lineas. \n");
            exit(EXIT_FAILURE);
        }
    }
}
void instalar_manejador_senhal(){
    if ( signal(SIGINT, manejador_senhal) == SIG_ERR ) {
        fprintf(stderr, "[MANAGER] Error al instalar el manejador de senhal: %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
void manejador_senhal(int sign){
    terminar_procesos();
    liberar_recursos();
    printf("[MANAGER] [MANAGER] Terminacion del programa (Ctrl + C). \n");
    exit(EXIT_SUCCESS);
}
void iniciar_tabla_procesos(int n_procesos_telefono, int n_procesos_linea){
    g_process_telefonos_table = malloc(n_procesos_telefono * sizeof (struct TProcess_t));
    g_process_lineas_table = malloc(n_procesos_linea * sizeof(struct TProcess_t));
    // Tabla de lineas
    for (int i = 0; i < n_procesos_linea; ++i) {
        g_process_lineas_table[i].pid = 0;
    }
    // Tabla de telefonos
    for (int i = 0; i < n_procesos_telefono; ++i) {
        g_process_telefonos_table[i].pid = 0;
    }
}
void crear_procesos(int numTelefonos, int numLineas){
    printf("[MANAGER] %d lineas creadas. ", numLineas);
    for (int i = 0; i < numLineas; ++i) {
        lanzar_proceso_linea(i);
    }
    printf("[MANAGER] %d telefonos creados. \n", numTelefonos);
    for (int i = 0; i < numTelefonos; ++i) {
        lanzar_proceso_telefono(i);
    }
}
void lanzar_proceso_telefono(const int indice_tabla){
    pid_t pid;
    switch ( pid = fork() ) {
        case -1:
            fprintf(stderr, "[MANAGER] Error al lanzar el proceso TELEFONO: %s \n", strerror(errno));
            terminar_procesos();
            liberar_recursos();
            break;
        case 0:
            if  ( execl(RUTA_TELEFONO, CLASE_TELEFONO, NULL ) == -1 ) {
                fprintf(stderr, "[MANAGER] Error al ejecutar la funcion execl en el proceso %s: %s \n", CLASE_TELEFONO,strerror(errno));
                exit(EXIT_FAILURE);
            }
    }
    // Actualizamos la tabla de procesos con el PID del nuevo proceso lanzado y su clase en este caso clase telefono.
    g_process_telefonos_table[indice_tabla].pid = pid;
    g_process_telefonos_table[indice_tabla].clase = CLASE_TELEFONO;
}
void lanzar_proceso_linea(const int indice_tabla){
    pid_t pid;
    switch ( pid = fork() ) {
        
    }
}
void esperar_procesos(){}
void terminar_procesos(void){}
void terminar_procesos_especificos(struct TProcess_t *process_table, int process_num){}
void liberar_recursos(){}
