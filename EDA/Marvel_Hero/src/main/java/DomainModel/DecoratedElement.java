/**
 * Clase contenedora que nos permite agregar información extra a un objeto.
 */
package DomainModel;

import graphsDSESIUCLM.Element;


/**
 * @version 0.1
 * @author Paulino Esteban Bermúdez Rodríguez | humancomputing.net
 */
public class DecoratedElement<T> implements Element {
    T element;
    boolean visited;
    DecoratedElement<T> parent;
    
    public DecoratedElement(T element) {
        this.element = element;
    }
    
    @Override
    public String getID() {
        return ((Personaje) element).getID();
    }
    
    public T getElement() {
        return element;
    }
    
    public boolean isVisited() {
        return visited;
    }
    
    public void setVisited(boolean value){
        visited = value;
    }
    
    public DecoratedElement<T> getParent() {
        return parent;
    }
    
    public void setParent(DecoratedElement<T> parent) {
        this.parent = parent;
    }
}
