package paulino.humancomputing;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


public class SocketServidor {
    public static void SocketServidor(String[] args) {
        if (args.length < 2 || args.length > 3) {
            System.err.println("Uso: java Main <servidor> <palabra> [<puerto>]");
            System.exit(1);
        }

        String servidor = args[0];
        String palabra = args[1];
        int puerto = (args.length == 3) ? Integer.parseInt(args[2]) : 7;

        try (Socket socket = new Socket(servidor, puerto);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
            
            // Enviar la palabra al servidor
            out.println(palabra);

            // Leer la respuesta del servidor
            StringBuilder respuesta = new StringBuilder();
            char[] buffer = new char[1024];
            int bytesLeidos;
            while ((bytesLeidos = in.read(buffer)) != -1) {
                respuesta.append(buffer, 0, bytesLeidos);
                if (respuesta.length() >= palabra.length()) {
                    break;
                }
            }
            
            // Mostrar la respuesta del servidor
            System.out.println("Respuesta del servidor: " + respuesta.toString());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

