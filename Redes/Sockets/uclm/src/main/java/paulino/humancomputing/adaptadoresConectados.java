package paulino.humancomputing;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

public class adaptadoresConectados {
    public static void adaptadoresConectados() {
        try {
            // Obtener enumeración de interfaces de red
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
            
            // Recorrer las interfaces de red
            while (interfaces.hasMoreElements()) {
                NetworkInterface interfaz = interfaces.nextElement();
                
                // Comprobar si la interfaz tiene conexión
                if (interfaz.isUp()) {
                    // Mostrar nombre de la interfaz
                    System.out.println("Interfaz: " + interfaz.getName());
                    
                    // Recorrer las direcciones IP de la interfaz
                    Enumeration<InetAddress> direccionesIP = interfaz.getInetAddresses();
                    while (direccionesIP.hasMoreElements()) {
                        InetAddress direccionIP = direccionesIP.nextElement();
                        
                        // Mostrar dirección IP de la interfaz
                        System.out.println("   Dirección IP: " + direccionIP.getHostAddress());
                    }
                }
            }
        } catch (SocketException e) {
            e.printStackTrace();
        }        
    }
}