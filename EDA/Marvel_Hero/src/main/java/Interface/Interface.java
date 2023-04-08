/** 
 * Interfaz de Marvel Hero Graph.
 * 
 * Esta clase es la encargada de representar todos los menús de operaciones que ve el usuario final.
 * Además de contener las constantes del programa.
 * 
 */
package Interface;

/**
 * @version 0.1
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public interface Interface {
    /**
     * Variables necesarias del programa.
     * FICHEROCSV Fichero CSV que contiene los datos con los que trabaja el programa 
     * SEPARADOR Caracter que separa los datos en el archivo CSV
     */    
    public static String FICHEROCSV = "src/main/java/Interface/marvel.csv";
    public static String SEPARADOR = ",(?=([^\"]*\"[^\"]*\")*[^\"]*$)";
    
    /**
     * Mensajes del programa.
     * Contiene:
     * - MENUPRINCIPAL
     * - FINPROGRAMA
     * - OPCION_NO_EXISTE
     */
    static final String MENUPRINCIPAL = """
                    ·······················································
                    ············· MENU PRINCIPAL - MARVEL HEROS ···········
                    ·······················································

                   Hola! Opciones: 
                   ________________________________________________________
                   1. Ver grafo con personajes + sociales & - sociables.
                   2. Imprimir el camino más corto entre dos personajes.
                   3. Diseñar el GREAT TEAMS de los personajes de Marvel.
                   ________________________________________________________
                   0. Salir del programa."
                   ·······················································
                                        Seleccione una opción: """;        
    
    static final String FINPROGRAMA = """
                                     Gracias por usar MARVEL EN LA UCLM. \n
                                      Y recuerda! \n
                                     \t Wakanda forever. - Black Panther.""";
    
    static final String OPCION_NO_EXISTE = """
                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''\n
                    '                       Warning!!!!!!!!               '\n
                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''\n
                                    OPCION NO VALIDA...\n\n                                           
                                           """;
    static final String OPCION_1 = """
                                   OPCION 1: Mostrar grafo con los personajes más sociables y menos sociables. \n\n
                                   \t Obteniendo datos: \n
                                   """;
    static final String OPCION_2 = """
                                   OPCION 2: Imprimir el camino más corto entre dos personajes. \n\n
                                   \t Obteniendo datos: \n
                                   """;
    static final String OPCION_3 = """
                                   OPCION 3. Diseñar el mejor equipo entre dos personajes datos. \n\n
                                   \t Obteniendo datos: \n
                                   """;
    /**
     * Métodos de llamada a los mensajes.
     * - MENU_MAIN
     * - OPCION_UNO
     */
    public static void MENU_MAIN(){ System.out.println(MENUPRINCIPAL);}
    public static void OPCION_UNO(){ System.out.println(OPCION_1); }
    public static void OPCION_DOS(){ System.out.println(OPCION_2);}
    public static void OPCION_(){ System.out.println(OPCION_3);}
    
}