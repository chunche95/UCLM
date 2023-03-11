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
    String username = System.getProperty ("user.name");
    public static String FICHEROCSV = "marvel.csv";
    public static String SEPARADOR = ";"; // ",(?=([^\\\"]*\\\"[^\\\"]*\\\")*[^\\\"]*$)\";
    
    /*
     * Mensajes del programa.
     */
    static final String MENUPRINCIPAL = """
                    ·······················································
                    ············· MENU PRINCIPAL - MARVEL HEROS ···········
                    ·······················································

                   Hola username , puedes: 
                   __________
                   1. Ver grafo con personajes + sociales & - sociables.
                   2. Imprimir el camino más corto entre dos personajes.
                   3. Diseñar el GREAT TEAMS de los personajes de Marvel.

                   0. Salir del programa."

                   ·······················································
                                        Seleccione una opción: """;        
    
    static final String FINPROGRAMA = """
                                     Gracias por usar MARVEL EN LA UCLM. 
                                      Y recuerda! 
                                     \t Wakanda forever. - Black Panther.""";
    
    static final String OPCION_NO_EXISTE = """
                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                    '                       Warning!!!!!!!!               '
                    '''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                    OPCION NO VALIDA...
                                           
                                           """;
    /*
     * Métodos que seran llamados 
     */
    public static void menuMain(){ System.out.println(MENUPRINCIPAL);}    
}