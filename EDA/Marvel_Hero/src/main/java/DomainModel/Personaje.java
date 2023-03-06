/**
 * 
 */
package DomainModel;

import graphsDSESIUCLM.Element;
/**
 * @version 0.1
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public class Personaje {
    
    private String nombre;
    
    public Personaje(String nombre){
        this.nombre = nombre;
    }
    
    public String getID() {
        return nombre;
    }
    
}
