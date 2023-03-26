/**
 * 
 */
package DomainModel;

import graphsDSESIUCLM.Element;
/**
 * @version 0.1.1
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public class Personaje implements Element{
    
    private String nombre;
    
    public Personaje(String nombre){
        this.nombre = nombre;
    }
    @Override
    public String getID() {
        return nombre;
    }
    
}
