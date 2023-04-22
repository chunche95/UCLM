import java.util.*;

public class Dominio {
    public static void main(String[] args) {
        int ladoFinca = 9;
        int[][] finca = new int[ladoFinca][ladoFinca];
        int[] cultivos = {2,3,5,8,10};
        // Ordenamos de mayor a menor
        Arrays.sort(cultivos);
        // Recorremos el array y lo pasado al metodo de distribucion de
        for (int inputC = 0; inputC < cultivos.length; inputC++) {
            distribuirCultivos(finca, inputC);
        }
        // Imprimir el cuadrado inicial
        for (int i = 0; i < ladoFinca; i++) {
            for (int j = 0; j < ladoFinca; j++) {
                System.out.print(" *");
            }
            System.out.println();
        }
        System.out.println("\n________________________________________________________________________\n");
        // Imprimir resultado
        for (int i = 0; i < ladoFinca; i++) {
            // Imprime las zonas libres primero
            for (int j = 0; j < ladoFinca; j++) {
                if (finca[i][j] == 0) {
                    System.out.print("L ");
                }
            }
            // Luego imprime los cultivos
            for (int j = 0; j < ladoFinca; j++) {
                if (finca[i][j] != 0) {
                    System.out.print("O ");
                }
            }
            System.out.println();
        }
    }

    private static void distribuirCultivos(int[][] finca, int tamCultivo) {
        for (int i = 0; i < finca.length; i++) {
            for (int j = 0; j < finca[i].length; j++) {
                if (finca[i][j] == 0 && i + tamCultivo <= finca.length && j + tamCultivo <= finca[i].length) {
                    boolean areaLibre = true;
                    for (int k = 0; k < tamCultivo; k++) {
                        for (int l = 0; l < tamCultivo; l++) {
                            if (finca[i + k][j + l] != 0) {
                                areaLibre = false;
                                break;
                            }
                        }
                        if (!areaLibre) {
                            break;
                        }
                    }
                    if (areaLibre) {
                        for (int k = 0; k < tamCultivo; k++) {
                            for (int l = 0; l < tamCultivo; l++) {
                                finca[i + k][j + l] = tamCultivo;
                            }
                        }
                        return;
                    }
                }
            }
        }
    }

        /* Utilizamos la interfaz Comparable para implementar el método compareTo de dicha interfaz.
	 * En este caso, compareTo se usa para establecer un orden entre objetos y luego los comparamos, devolviendonos un valor si el
	 * objeto actual es menor, igual o mayor que el objeto comparado. 
	 * @see Comparable
	 * @author pauli
	 *
	 */
    class Cultivo implements Comparable<Cultivo> {
    	private int t;
    	
    	public Cultivo(int t) {
    		this.t = t;
    	}
    	
    	public int getTam () {
    		return t;
    	}
    	@Override
    	public int compareTo(Cultivo otro) {
    		// Ordenar por tamaño de forma desendente.
    		return otro.t -t ;
    	}
    }
}