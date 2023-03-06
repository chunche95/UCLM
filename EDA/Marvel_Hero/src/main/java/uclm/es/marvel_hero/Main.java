/**
 * <h1>Proyecto de estructuras de datos no lineales. Grafos.</h1>
 * <h2>Análisis de colaboraciones entre personakes del universo Marvel.</h2>
 * Descripción:
 * En <a href="https://github.com/melaniewalsh/sample-social-network-datasets/tree/master/sample-datasets/marvel" target="_blank" rel="noopener noreferrer">Repositorio MelanieWalsh - Marvel</a>
 * se encuentra el fichero CSV  que representa una red de relaciones entre personajes de la editorial Marvel. 
 * En cada línea, se tiene el nombre del personaje e indica un número entero positivo que representa las interacciones que estos han tenido.
 * 
 * El objetivo de este trabajo es diseñar e implementar un programa en Java que procese el fichero indicado y realice las siguientes tareas:
 * 
 * <ul>
 *  <ol> a+ Construir un grafo y 
 *       - Mostrar el número de personajes, 
 *       - el número total de relaciones entre personajes, 
 *       - el personaje más sociable y 
 *       - el personaje que menos trabaja en equipo. (Si hay más de un personaje que cumpla la condición, mostrarlos todos) 
 * </ol>
 * <ol>   
 *       b- Determinar la sucesión más corta de personajes que conecte a dos personajes dados.
 * </ol>
 * <ol>
 *       c+ Diseñar un equipo formado a partir de dos personajes
 *        - con pocas interacciones
 *        - Nº de interacciones entre personajes no debe ser <10
 *        - en caso de no existir, debe indicarse.
 * </ol>
 * </ul>
 */
package uclm.es.marvel_hero;

import DomainModel.DecoratedElement;
import static DomainModel.Methods.CargarDatos;
import DomainModel.Personaje;
import Interface.Interface;

/**
 * @versiono 0.1.2
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public class Main {
    public static void main(String[] args) {
        // Cargamos los datos del CSV a nuestro grafo de Personajes de Marvel.
        graphsDSESIUCLM.Graph <DecoratedElement<Personaje> , Integer> grafo = CargarDatos();
        // Lanzamos el menu de opciones del programa.
        Interface.menuMain();
        // Obtenemos la opción seleccionada y la devolvemos a las operaciones disponibles.
        
    }
}
