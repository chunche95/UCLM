# Preparando ejercicio test.
Implementación de un algoritmo de sincronización, el de Cristian o el de Berkeley, mediante invocaciones ZeroC Ice

# Algoritmo de Cristian 
Es un algoritmo de sincronización de reloj que se usa para sincronizar la hora con un servidor de hora mediante procesos de cliente.
Este algoritmo funciona bien con redes de baja latencia donde el tiempo de ida y vuelta es corte en comparación con la precisión, mientras que los sistemas/apliciones distribuidas propensas a la redundancia no van de la mano con este algoritmo.

El tiempo de ida y vuelta se refiere al tiempo de duracion entre el inicio de la solicitud y el final de la respuesta correspondiente.

## Algoritmo.
1. Cliente envía la solicitud para obtener la hora del reloj (la hora en el servidor) al servidor del reloj a la hora T0.
2. El servidor de reloj escucha la solicitud realizada por el proceso del cliente y devuelve la respuesta en forma de hora del servidor de reloj.
3. El proceso del cliente obtiene la respuesta del servidor de reloj a la hora T1 y calcula la hora sincronizada del reloj del cliente usando la fórmula siguiente:

$$ T_cliente=T_server+((T_1-T_0))/2 $$

** El error en la sincronización puede ser como máximo de $$ (T_1-T_0)/2 $$ segundos como máximo. ** 
$$ error ∈[-(T_1-T_0)/2,(T_1-T_0)/2] $$

### Programa python
#### Server
```py
import socket
import datetime

# Function user to initiate the clock server
def initiateClockServer():
    
    ssock = socket.socket() # Socket socket 
    print("Socket successfully established") 
    
    sport = 8000 # Server port number 
    ssock.bind(()'', sport)) # Socket server address and port number to connect 

    # Start listening for requests
    ssock.listen(5) # Start listening for requests
    print("Listening for requests...")
    
```

# Algoritmo de Berkeley
