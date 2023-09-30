#!/usr/bin/env python3

#################################################################################################
# El cliente, crea un objeto socket, lo utiliza .connect() para conectarse al servidor
# y lo llama s.sendall() para enviar su mensaje al servidor. Por último, llama 
# s.recv() para leer la respuesta del servidor y luego la imprime.
#################################################################################################

import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server
try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(b'Hello, world!')
        data = s.recv(1024)
        print('Received', repr(data))
        s.close()
        print('Connection closed')
    print(f'Received {data!r}')
except ConnectionRefusedError:
    print('Connection refused')
    print('Error: El servidor no está en ejecución o no está escuchando en el puerto especificado.')
except socket.error as msg:
    print(f'Connection error: {msg}')
except Exception as e:
    print(f'Error inesperado: {e}')
