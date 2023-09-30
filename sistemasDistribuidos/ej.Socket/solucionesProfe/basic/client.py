#!/usr/bin/env python3

# Script en python para la parte de la comunicacion del cliente usando sockets
# Se comunica con el servidor usando la IP localhost y el puerto 4000, configurados en la parte del servidor.
#
# Help:
# -> Parametros de entrada:
# --> Parametro 1: IP:PORT
# --> Parametro 2: Mensaje enviado al servidor usando codificación ascii (128) 
# Example:
# ./client localhost:4000 'Mensaje enviado al servidor usando codificación ascii'


import socket, sys

# Entrada por terminal de IP de servidor y puerto, separados por ':'
HOST, PORT = sys.argv[1].split(':')
# Segundo argumento de entrada por terminal, el mensaje que envia el cliente
MSG = sys.argv[2]

# Programa
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client: 
    client.sendto(MSG.encode('ascii'), (HOST, int(PORT)))