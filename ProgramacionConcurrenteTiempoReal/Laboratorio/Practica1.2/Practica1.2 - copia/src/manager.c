/*
* Practica1.2.c: define el punto de entrada de la aplicación.
*/

/**
 * Objetivos generales.
 * --------------------
 * Resolver un problema básico de getión de procesos que sirva para que el alumno conozca y maneje las primitivas POSIX para llevar a cabo dicha gestión.
 *
 * Objetivos especificos.
 * ----------------------
 * Adquirir las habilidades necesarias para la creación  y espera de procesos, asó como el correcto tratamiento de las señales básicas relativas a laa finalización de la aplicación.
 * Implementar la solución planteada mediante las primitivas POSIX para la gestión de procesos, haciendo uso de la funcionalidad necesaria para resolver el problema dependiente del dominio planteado.
 *
 * Especificación.
 * ---------------
 * Sistema compuesto por tres ejecutables que simule el funcionamiento de tres tipos de procesos:
 * (X) 1. Manager.
 *  () 1.1 Responsable de crear un número determinado de procesos de tipo procesador y de tipo contador.
 *  () 1.2 Gestionar de manera adecuada su finalzación y liberación de recursos.
 *  () 1.3 Recibe por parametro la ruta de dos ficheros
 *      () 1.3.1 archivo_texto - Será abierto por el proceso manager.
 *          () 1.3.1.1 Leerá su contenido linea a linea.
 *          () 1.3.1.2 Por cada linea creará un proceso contador.
 *      () 1.3.2 archivo_patrones - Será el procesado por el proceso manager.
 *          () 1.3.2.1 Leerá el contenido palabra a palabra
 *          () 1.3.2.2 Por cada palabra insertará un nodo en una lista empleando la estructura de datos creada en la practica 1.1
 *          () 1.3.2.3 Procesando dicha lista, creará un proceso procesador por cada nodo de la misma.
 * () 1.4 El usuario pulsa la combinación de teclas Ctrl + C. El proceso manager envia una señal de finalización a todos los procesos de tipo procesador y contador en ejecución y libera recursos.
 * () 2. Procesador.
 *  () Recibirán el el  momento de su creación la ruta del fichero archivo_texto y un patron.
 *  () Sun función consistirá en comprobar si este patron se corresponde con alguna de las palabras que conforman el texto contenido en el fichero archivo_texto.
 * () 3. Contador.
 *  () Recibirán en el momento de su creación un número de linea y una linea.
 *  () Su función: Contar el número de palabras que conforman la linea recibida.
 *
 * () Las rutas de los archivos seran indicados por el usuario a traves de la linea de ordenes al ejecutar el único proceso de tipo manager.
 *      ./exec/manager archivo_texto archivo_patrones
 *
*/

#include "manager.h"
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
#include <lista.h>
#include <cstdio>
#include <cstdio>

void procesar_argumentos(int argc, char* argv[], char** filename, char** pattern, int* lines);
void controlador_de_senhal();
void control_senhal(int sign);
void procesar_patrones(const char* fichero_patrones);
void procesar_linea(char* linea);
void iniciar_tabla_procesos(int n_procesos_contador, int n_procesos_procesador);
void crear_procesos(const char* nombre_fichero);
void lanzar_proceso_contador(const int indice_tabla, const char* linea, const char* numero_linea_str);
void lanzar_proceso_procesador(const int indice_tabla, const char* patron, const char* nombre_fichero);
void esperar_procesos();
void terminar_procesos(void);
void liberar_recursos();

int g_nProcesos;
struct TProcesos_t* g_tabla_procesos;
TLista *patrones;

int main(int argc, char *argv[]) {
	printf("\n");
	/**
	* Declaramos las variables necesarias para la ruta de los ficheros.
	*/
	char* nombre_fichero = NULL;
	char* fichero_patrones = NULL;
	// Contadores necesarios
	int lineas = 0;
	patrones = malloc(sizeof(TLista));

	crear(patrones, "Patrones");
	/**
	* Funciones 
	*/
	procesar_argumentos(argc, argv, &nombre_fichero, &fichero_patrones, &lineas);
	control_de_sennal();
	procesar_patrones(fichero_patrones);
	iniciar_tabla_procesos(lineas, longitud(patrones) - 1);
	crear_procesos(nombre_fichero);
	esperar_procesos();

	printf("...........................................................");
	printf("\n Todos los procesos terminados del proceso Manager. \n");
	printf("...........................................................");
	liberar_recursos();

	return 0;
}

void procesar_argumentos(int argc, char* argv[], char** fichero_nombre, char** fichero_patrones, int* lineas) 
{
	FILE *fichero;
	int ch;
	// Controlamos el nº de argumentos pasados por parametro en la terminal
	if (argc != 3)
	{
		printf("Error: Los argumentos pasados por terminal son incorrectos.");
		printf("");
		printf(" Ejemplo de ejecución: \n ./exec/manager <fichero> <fichero_patrones>");
		printf("");
		return 1;
	}
	*fichero_nombre = argv[1];
	*fichero_patrones = argv[2];
	if ((fichero = fopen(*fichero_nombre, "r")) == NULL)
	{
		printf("Error: Fallo inesperado al abrir el fichero. \n");
		return 1;
	}
	// Encontrado el fichero, contamos el nº de lineas que tiene
	while ((ch = fgetc(fichero)) != EOF) {
		if (ch == '\n')
		{
			*lineas += 1;
		}
	}
	fclose(fichero);
}

void controlador_de_senhal() {
	if (signal(SIGINT, control_senhal) == SIG_ERR)
	{
		printf(" Error: Fallo al instalar el controlador de señal. ");
		return 1;
	}
}

void control_senhal(int sign) {
	printf(" Programa MANAGER finalizado con Ctrl+C. \n");
	terminar_procesos();
	liberar_recursos();
	return 0;
}

void procesar_patrones(const char* fichero_patrones)
{
	FILE *fichero;
	char linea[PATH_MAX];
	if ( (fichero = fopen(fichero_patrones, "r")) == NULL)
	{
		printf("Error: Fallo al abrir el fichero de patrones.\n");
	}
	while (fgets(linea, sizeof(linea), fichero) != NULL) {
		procesar_linea(linea);
	}
	fclose(fichero);
}
void procesar_linea(char* linea) 
{
	char *token;
	token = strtok(linea, " ");
	while (token != NULL) {
		insertarFinal(patrones, token);
		token = strtok(NULL, " ");
	}
}
void iniciar_tabla_procesos(int n_procesos_contador, int n_procesos_procesador) 
{
	g_nProcesos = n_proceso_contador + n_proceso_procesador;
	g_tabla_procesos = malloc(g_nProcesos * sizeof(struct TProcess_t));

	for (int i = 0; i < g_nProcesos; i++)
	{
		g_tabla_procesos[i].pid = 0;
	}
}
void crear_procesos(const char* nombre_fichero) 
{
	FILE *fichero;
	char linea[PATH_MAX], numero_linea_str[3];
	int indice_tabla = 0;

	if ( ( fichero = fopen(nombre_fichero, "r")) == NULL)
	{
		printf(numero_linea_str + " " + nombre_fichero); 
		return 1;
	}
	while (fgets(linea, sizeof(linea), fichero) != NULL) {
		printf(numero_lineas_str + " " + indice_tabla);
		lanzar_proceso_contador(indice_tabla, linea, numero_linea_str);

		indice_tabla++;
	}
	for (int i = 0; i < longitud(patrones); i++)
	{
		lanzar_proceso_procesador(indice_tabla, getElementoN(patrones, (i - 1)), nombre_fichero);
		indice_tabla++;
	}
	printf("manager: Procesos han sido creados. " + indice_tabla + "\n");
	sleep(2);
	fclose(fichero);
}
void lanzar_proceso_contador(const int indice_tabla, const char* linea, const char* numero_linea_str) 
{
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			printf("Error manager: Fallo al ejecutar execl() en el proceso " CLASE_CONTADOR);
			terminar_procesos();
			liberar_recursos();
			return 1;
		case 0:
			if ( execl(RUTA_CONTADOR, CLASE_CONTADOR, linea, numero_linea_str, NULL )  == -1)
			{
				printf("Error: Fallo en Manager al ejecutar execl() en el proceso " + CLASE_CONTADOR);
				return 1;
			}
	}
	g_tabla_procesos[indice_tabla].pid = pid;
	g_tabla_procesos[indice_tabla].clase = CLASE_CONTADOR;
}
void lanzar_proceso_procesador(const int indice_tabla, const char* patron, const char* nombre_fichero) {
	pid_t pid;
	switch (pid = fork()) 
	{
		case -1:
			printf("Error: Fallo al lanzar el proceso procesador. \n");
			terminar_procesos();
			liberar_recursos();
			return 0;
		case 0:
			if ( execl (RUTA_PROCESADOR, CLASE_PROCESADOR, nombre_fichero, patron, NULL) == -1)
			{
				printf("Error: Fallo al ejecutar execl() en el proceso " + CLASE_PROCESADOR);
				return 0;
			}
	}

	g_tabla_de_procesos[indice_tabla].pid = pid;
	g_tabla_de_procesos[indice_tabla].clase = CLASE_PROCESADOR;
}
void esperar_procesos() {
	int i;
	int n_procesos = g_nProcesses;
	pid_t pid;

	while (n_procesos > 0) {
		pid = wait(NULL);
		for ( i = 0; i < g_nProcesses; i++)
		{
			if ( pid == g_tabla_procesos[i].pid )
			{
				printf(" Manager: Proceso terminado ");
				g_tabla_procesos[i].pid = 0;
				n_procesos--;
				break;
			}
		}
	}
}
void terminar_procesos(void) {
	int i;
	printf(" Manager: Terminar con los procesos hijos en ejecución. \n");
	for (size_t i = 0; i < length; i++)
	{
		if (g_tabla_procesos[i].pid != 0)
		{
			printf("Manager: Proceso finalizado " + g_tabla_procesos[i].close + " - " + g_tabla_procesos[i].pid + "\n");
			if (kill(g_tabla_procesos[i].pid, SIGINT) == -1)
			{
				printf("Error: fallo al lanzar la señal kill() en el proceso " + g_tabla_procesos[i].pid + " ··> " strerror(errno));
			}
		}
	}
}
void liberar_recursos() {
	free(g_tabla_procesos);
	destruir(patrones);
}