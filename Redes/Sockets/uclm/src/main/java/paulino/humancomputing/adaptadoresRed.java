package paulino.humancomputing;

/**
 * Crea un programa que muestre el nombre de tu host y una
 * lista de las direcciones IPs de tus adaptadores de red:
 * • Utiliza el método estático getLocalHost de InetAddress para obtener el objeto localhost
 * • Utiliza el método getAllByName pasando como parámetro el nombre canónico del localhost (getCanonicalHostName)
 * • Recorre el array que devuelve
 */
import java.net.InetAddress;
import java.net.UnknownHostException;

public class adaptadoresRed {
    public static void adaptadoresRed() {
        try {
            // Obtener objeto localhost
            InetAddress localHost = InetAddress.getLocalHost();
            
            // Mostrar nombre del host
            System.out.println("Nombre del host: " + localHost.getHostName());
            
            /* Obtener direcciones IP de los adaptadores de red  */
            InetAddress[] direccionesIP = InetAddress.getAllByName(localHost.getCanonicalHostName());
            
            // Mostrar lista de direcciones IP
            System.out.println("Direcciones IP de los adaptadores de red:");
            for (int i = 0; i < direccionesIP.length; i++) {
                System.out.println("   " + direccionesIP[i].getHostAddress());
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
