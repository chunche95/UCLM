/**
 * DomainModel. 
 * Paquete de programa encargado de almacenar losmetodos princiaples del funcionamiento de la aplicación.
 * 
 * <h2>Methods</h2>
 * Clase principal, llama la funcionalidad lógica del programa.
 * El contenido de la clase es:
 * - Cargar Datos
 * - Operar los datos de entrada
 * - Devolver los datos de salida
 * - Actualizar los datos del grafo.
 * - Consultar los datos - @see graphsDSSIUCLM.Graph
 * (*) Borrar dato de entrada + actualización del grafo.
 */
package DomainModel;

import static Interface.Interface.*;
import graphsDSESIUCLM.*;

import java.io.*;
import java.util.*;

/**
 * @version 0.2.2
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public class Methods {
    private static Scanner sc;
    
    /** *********************************
     * Principales Métodos de operaciones 
     ************************************ */
    /**
     * Cargamos los datos del CSV en el grafo llamado CargarDatos 
     * @return devuelve el grafo con los datos
     */
    public static Graph<DecoratedElement<Personaje>, Integer> CargarDatos() {
        Graph<DecoratedElement<Personaje>, Integer> grafoResultante = new TreeMapGraph<>();
        try {
            sc = new Scanner(new File(FICHEROCSV));
            String linea = sc.nextLine();            
            do {                
                linea = sc.nextLine();
                String[] splitted = linea.split(SEPARADOR);
                grafoResultante.insertEdge(
                        new DecoratedElement<>(new Personaje(splitted[0])), 
                        new DecoratedElement<>(new Personaje(splitted[1])), 
                        Integer.valueOf(splitted[2]));                
            } while (sc.hasNextLine());
            sc.close();            
            return grafoResultante;
        } catch (IOException ex) {
            System.out.println(ex.getLocalizedMessage());
            System.exit(1);
            return null;
        }
    }    
    /*
     * Mostramos los datos almacenados en el Grafo
     */
    public static void datosAlmacenados() {
        Graph<DecoratedElement<Personaje>, Integer> grafo = CargarDatos();
        Iterator<Vertex<DecoratedElement<Personaje>>> iter = grafo.getVertices();

        while (iter.hasNext()) {
            Vertex<DecoratedElement<Personaje>> vertex = iter.next();
            DecoratedElement<Personaje> element = vertex.getElement();
            System.out.println(element.getElement().getID());
        }

    }

    /**
     * Menu Principal del programa.
     * Muestra las opciones disponibles del programa y trabaja con ellos a partir de los datos de entrada.
     * @param grafo 
     */
    public static void MenuOperaciones( Graph<DecoratedElement<Personaje>, Integer> grafo) {
        while (true) {
            // Mostramos las acciones disponibles del menu
            Interface.Interface.MENU_MAIN();
            // Recogemos la opcion marcada por el usuario
            sc = new Scanner(System.in); 
            // Trabajamos los datos del grafo antes de sacar los resultados
            //------------------------------------------------------------------------------
            // Creamos una lista de los vertices existentes
            List<Vertex<DecoratedElement<Personaje>>> vertices = crearListaVertices(grafo.getVertices());
            // Generamos una lista con las aristas existentes
            Collections.sort(vertices, ((a , b) -> crearListaAristas(grafo.incidentEdges(b)).size() - crearListaAristas ( grafo.incidentEdges(a)).size()));
            //
            Vertex<DecoratedElement<Personaje>> inicio = null;
            Vertex<DecoratedElement<Personaje>> fin = null;
            //------------------------------------------------------------------------------            
            // Opciones disponibles, con las que podemos trabajar
            switch (sc.nextInt()) {
                case 1:
                    OPCION_UNO();
                    cantidadPersonajes(grafo, vertices); // nº de personajes totales del grafo
                    break;
                case 2:
                    OPCION_DOS();
                    caminoEncontrado(grafo, vertices); // camino entre dos personajes
                case 3:
                    OPCION_TRES();
                    crearEquipo(grafo, vertices, inicio, fin); // generamos un equipo entre dos personajes
                case 4:
                    menuFinal(); // fin del programa
                default:
                    opcionNoExiste(); // opcion escrita, no existe en el programa
            }
        }
    }
    
    /* ***************************************** */
    /* OPCIONES OPERADORAS DEL PROGRAMA MARVEL   */
    /* ***************************************** */  
    
    /**
     * Devuelve la cantidad de personajes.
     * @param grafo
     * @param vertices 
     */
    private static void cantidadPersonajes(Graph grafo, List<Vertex<DecoratedElement<Personaje>>> vertices) {
        System.out.println("Cantidad de personajes: "+grafo.getN());
        System.out.println("Cantidad de relaciones: "+grafo.getM());
        mostrarMayor(vertices, grafo);
        mostrarMenor(vertices, grafo);
    }
    /**
     * Encuentra el camino entre dos personajes.
     * @param vertices
     * @param grafo 
     */
    private static void caminoEncontrado(Graph grafo, List<Vertex<DecoratedElement<Personaje>>> vertices) {
        for ( Vertex<DecoratedElement<Personaje>> vertex : vertices ) {
            System.out.println(vertex.getID());
        }
        sc.nextLine();
        Vertex<DecoratedElement<Personaje>> inicio = obtenerPersonaje(vertices, sc);
        Vertex<DecoratedElement<Personaje>> fin = obtenerPersonaje(vertices, sc);
        DecoratedElement<Personaje> inicioPersonaje = inicio.getElement();
        if ( realizarCamino(grafo, fin, inicio)) {
            recorrerCamino(inicioPersonaje);
            System.out.println(fin.getID());
        } else {
            System.out.println("No se ha encontrado ningun camino");
        }        
    }    
    /**
     * Crea un equipo a partir de un personaje existente en el grafo y genera un equipo de 10 personajes a partir de él.
     * @param grafo
     * @param vertices
     * @param inicio
     * @param fin 
     */
    private static void crearEquipo(Graph grafo, List<Vertex<DecoratedElement<Personaje>>> vertices, Vertex<DecoratedElement<Personaje>> inicio, Vertex<DecoratedElement<Personaje>> fin) {
        vertices.forEach(a -> System.out.println(a.getID()) );
        sc.nextLine();
        inicio = obtenerPersonaje(vertices, sc);
        fin = obtenerPersonaje(vertices, sc);
        equipoVertices(grafo, fin, inicio);
        if ( inicio.getElement().getParent() != null ) {
           recorrerCamino(inicio.getElement());
            System.out.println(fin.getID());
        } else {
            System.out.printf("No se ha encontrado equipo para %s y %s ", inicio.getID(), fin.getID());
        }
    }
    /**
     * 
     * @param personajesMarvel
     * @param grafo 
     */
    private static void mostrarMayor(List<Vertex<DecoratedElement<Personaje>>> personajesMarvel, Graph<DecoratedElement<Personaje>, Integer> grafo) {
        try {
            System.out.printf("El personaje con mayor número de relaciones es: %s \n", personajesMarvel.get(0).getID());
            for (int i = 1 ; i < personajesMarvel.size() - 1 ; i++) {
                if ( crearListaAristas(grafo.incidentEdges(personajesMarvel.get(i))).size() == crearListaAristas(grafo.incidentEdges(personajesMarvel.get(0))).size() ) {
                    System.out.println("El personaje con mayor número de relaciones es: " + personajesMarvel.get(i).getID());
                }
            }
        } catch (NoSuchElementException e) {
            System.out.println("Grafo sin datos!!! - No se han encontrado elementos en el grafo. \n" + e);
        }
    }
    /**
     * 
     * @param personajesMarvel
     * @param grafo 
     */
    private static void mostrarMenor(List<Vertex<DecoratedElement<Personaje>>> personajesMarvel, Graph<DecoratedElement<Personaje>, Integer> grafo) {
        try {
            System.out.printf("El personaje con menor número de relaciones es: %s \n", personajesMarvel.get(personajesMarvel.size()-1).getID());
            for (int i = personajesMarvel.size()-2 ; i >= 0 ; i--) {
                if ( crearListaAristas(grafo.incidentEdges(personajesMarvel.get(i))).size() == crearListaAristas(grafo.incidentEdges(personajesMarvel.get(personajesMarvel.size() -1 ))).size() ) {
                    System.out.println("El personaje con menor número de relaciones es: " +  personajesMarvel.get(i).getID());
                }
            }
        } catch ( NoSuchElementException e ) {
            System.out.println("Grafo sin datos!!! - No se han encontrado elementos en el grafo. \n" + e);
        }
    }
    /**
     * 
     * @param personajes
     * @param scanner
     * @return 
     */
    private static Vertex<DecoratedElement<Personaje>> obtenerPersonaje ( List<Vertex<DecoratedElement<Personaje>>> personajes, Scanner scanner ) {
        System.out.println("Escriba el nombre del personaje: ");
        String nombre  = sc.nextLine();
        if (nombre.equals("")) {            
            return obtenerPersonaje(personajes, scanner);
        } else {
            for ( Vertex<DecoratedElement<Personaje>> vertex : personajes ) {
                if ( vertex.getID().equals(nombre) ) {
                    return vertex;
                }                
            }
            return obtenerPersonaje(personajes, scanner);
        }
    }  
    /**
     * 
     * @param graph
     * @param inicio
     * @param fin
     * @return 
     */
    private static boolean realizarCamino(Graph<DecoratedElement<Personaje>, Integer> graph, Vertex<DecoratedElement<Personaje>> inicio, Vertex<DecoratedElement<Personaje>> fin ) {
        LinkedList<Vertex<DecoratedElement<Personaje>>> queue = new LinkedList<>();
        queue.add(inicio);
        boolean acabar = false;
        do {
            Vertex<DecoratedElement<Personaje>> v = queue.poll();
            Iterator<Edge<Integer>> vertices = graph.incidentEdges(v);
            while( vertices.hasNext()  && !acabar ) {
                Vertex<DecoratedElement<Personaje>> adVertex = graph.opposite(v, vertices.next());
                try {
                    acabar = adVertex.equals(fin);
                    if ((adVertex.getElement().getParent() == null ) && !(adVertex.equals(inicio))) {
                        queue.add(adVertex);
                        adVertex.getElement().setParent(v.getElement());
                    }
                } catch (NullPointerException e) {
                    System.out.println(e);
                }
            }
        } while (fin.getElement().getParent() == null && !queue.isEmpty() &&  !acabar);
        return acabar;
    }    
    /**
     * 
     * @param Integer
     * @return inicio
     */
    private static Vertex<DecoratedElement<Personaje>> equipoVertices (  Graph<DecoratedElement<Personaje>, Integer> graph, Vertex<DecoratedElement<Personaje>> inicio, Vertex<DecoratedElement<Personaje>> fin) {
        Edge<Integer> e = null;
        inicio.getElement().setVisited(true);
        Iterator<Edge<Integer>> it = graph.incidentEdges(inicio);
        Vertex<DecoratedElement<Personaje>> nodoAux = null;
        while ( it.hasNext() && !(inicio.equals(fin))) {
            e = it.next();
            nodoAux = graph.opposite(inicio, e);
            if ( !nodoAux.getElement().isVisited() && e.getElement() < 10 ) {
                nodoAux.getElement().setParent(inicio.getElement());
                equipoVertices(graph, nodoAux, fin);
            }
        }
        return inicio;
    }    
    /**
     * 
     * @param personaje 
     */
    private static void recorrerCamino(DecoratedElement<Personaje> personaje ) {
        while ( personaje.getParent() != null ) {
            System.out.println(personaje.getID() + " -> ");
            personaje = personaje.getParent();
        }
    }    
    /**
     * 
     * @param iterator
     * @return list
     */
    private static List<Vertex<DecoratedElement<Personaje>>> crearListaVertices ( Iterator<Vertex<DecoratedElement<Personaje>>> iterator ) {
        List<Vertex<DecoratedElement<Personaje>>> list = new ArrayList<>();
        while (iterator.hasNext()) {
            list.add(iterator.next());
        }
        return list;
    }    
    /**
     * 
     * @param iterator
     * @return list
     */
    private static List<Edge<Integer>> crearListaAristas (Iterator<Edge<Integer>> iterator) {
        List<Edge<Integer>> list = new ArrayList<>();
        while (iterator.hasNext()) {
            list.add(iterator.next());
        }
        return list;
    }   
    /**
     * 
     * @return 
     */
    
    /*private static Graph<DecoratedElement<Personaje>, Integer> cargarDatosPruebas() {
        Graph<DecoratedElement<Personaje>, Integer> grafo = new TreeMapGraph<DecoratedElement<Personaje>, Integer>();
        Personaje[] personajes = new Personaje[10];
        for (int i = 0; i < 10; i++) {
            personajes[i] = new Personaje(" " + (char) ('a' + i));
        }
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[0]), new DecoratedElement<Personaje>(personajes[1]), 2);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[0]), new DecoratedElement<Personaje>(personajes[2]), 8);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[0]), new DecoratedElement<Personaje>(personajes[4]), 12);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[2]), new DecoratedElement<Personaje>(personajes[3]), 24);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[4]), new DecoratedElement<Personaje>(personajes[5]), 6);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[5]), new DecoratedElement<Personaje>(personajes[5]), 4);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[6]), new DecoratedElement<Personaje>(personajes[6]), 3);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[6]), new DecoratedElement<Personaje>(personajes[7]), 5);
        grafo.insertEdge(new DecoratedElement<Personaje>(personajes[8]), new DecoratedElement<Personaje>(personajes[8]), 32);
        return grafo;
    }
    */
    
    
    /* ***************************************** */
    /* OPCIONES FINALES DEL PROGRAMA & MENSAJES  */
    /* ***************************************** */  
    /**
     * Mensaje fin del programa.
     */
    private static void menuFinal() { System.out.println(FINPROGRAMA); sc.close();}    
    /**
     * Mensaje de control para una opción no existente.
     */
    private static void opcionNoExiste() { System.out.println(OPCION_NO_EXISTE); }
    
}
