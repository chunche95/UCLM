#!/usr/bin/python3
import socket
import argparse
import struct

'''
#      _       _        
#   __| | __ _| |_ __ _ 
#  / _` |/ _` | __/ _` |
# | (_| | (_| | || (_| |
#  \__,_|\__,_|\__\__,_|
'''
## Datos de conexión
DIRECCIONIP='localhost'
PUERTO=12345
## Configuraciones de servidor
SERVER_UDP = socket.socket( socket.AF_INET , socket.SOCK_DGRAM )
SERVER_UDP_ADDR = (DIRECCIONIP, PUERTO) 

'''
#  ___  ___ _ ____   _____ _ __ 
# / __|/ _ \ '__\ \ / / _ \ '__|
# \__ \  __/ |   \ V /  __/ |   
# |___/\___|_|    \_/ \___|_|   
'''
## Funciones del Servidor
def server():
    print(f"Iniciando servidor en {SERVER_UDP_ADDR[0]} con el puerto: {SERVER_UDP_ADDR[1]} ")
    print("Esperando mensaje...")
    with SERVER_UDP as s:        
        s.bind(SERVER_UDP_ADDR)
        print(f"Servidor UDP corriendo en  {DIRECCIONIP}:{PUERTO}")
        while 1:
            data, addr = s.recvfrom(1024) # Datos del cliente - Máx. 1024 bytes.
            print(f"Recibido {data.decode()} desde  {addr}")
            # Procesar los datos y enviar la respuesta
            ## Desempaquetado del mensaje
            unpacked_data = struct.unpack("!I", data) # Esperamos un entero de 4 bytes (! = big endian)
            print(f"Datos desempaquetados: {unpacked_data[0]}")
            ## Enviar una respuesta al cliente
            response = struct.pack('!I', unpacked_data[0] + 1) # Responder incrementando el valor recibido
            s.sendto(response, addr)
            print("Respuesta enviada")

'''
#      _ _            _   
#  ___| (_) ___ _ __ | |_ 
# / __| | |/ _ \ '_ \| __|
#| (__| | |  __/ | | | |_ 
# \___|_|_|\___|_| |_|\__|
'''

## Funciones del Cliente
def client(number):
    with SERVER_UDP as s:
        # Empaquetamos el número entero usando struct
        data = struct.pack("!I", number)
        # Enviamos los datos empaquetados al servidor
        s.sendto(data, ('localhost', 12345))
        print(f"Enviando {data.decode()} al servidor {DIRECCIONIP}:{PUERTO}")
        # Recibir respuesta del servidor
        data, _ = s.recvfrom(1024)
        # Desenpaquetamos la respuesta
        unpacked_data = struct.unpack('!I', data) # Empaquetar el número entero 'number' en formato 'big indian (!) como un entero de 4 bytes (I)
        print(f"Recibido {unpacked_data[0]-1} del servidor {DIRECCIONIP}:{PUERTO}")

'''
#                  _       
#  _ __ ___   __ _(_)_ __  
# | '_ ` _ \ / _` | | '_ \ 
# | | | | | | (_| | | | | |
# |_| |_| |_|\__,_|_|_| |_|
'''
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Servidor UDP en Python")
    parser.add_argument(
        '-m', '--mode',
        type = str,
        choices = ['server', 'client'],
        default = 'server',
        help = 'Select exec mode'
    )

    args = parser.parse_args()
    server() if args.mode == "server" else client(9)
