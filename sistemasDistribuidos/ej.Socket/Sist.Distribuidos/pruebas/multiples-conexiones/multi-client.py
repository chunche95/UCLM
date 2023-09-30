#!/usr/bin/env python3

import socket, argparse

def arguments():
    parser = argparse.ArgumentParser(description="Cliente para el servidor multiconexión")
    parser.add_argument("host", nargs='?', default='localhost', type=str, help="Dirección IP del servidor (opcional)")
    parser.add_argument("port", nargs='?', default=65432, type=int, help="Puerto del servidor")
    # Parsear los argumentos de la línea de comandos
    args = parser.parse_args()
    return args.host, args.port

def is_ascii(s):
    return all(ord(c) < 128 for c in s)

def main():
    try:
        # Obtener los argumentos de la línea de comandos (opcionales)
        HOST, PORT = arguments()
        # Conectarse al servidor
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            while True:
                message = input('Write a message or write "exit" to exit: ')
                if message.lower() == 'exit':
                    break
                if not is_ascii(message):
                    print('ASCII only')
                    continue
                s.sendall(message.encode('ascii')) # Devuelve la cantidad de bytes enviados, que puede ser menor que el tamaño de la petición. 
                data = s.recv(1024) # Cantidad máxima de datos que se recibirán a la vez.
                print('Received', repr(data))
                print(f'Respuesta del servidor: {data.decode("ascii")}')
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

if __name__ == "__main__":
    main()