#!/usr/bin/env python3

# Script python para la parte de servidor, resuelve los mensajes de tipo utf-8 recibidos de tamaño 1024
# Usando la dirección localhost y el puerto 4000 para la comunicación cliente-servidor.

import socket

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind(('127.0.0.1', 4000 ))
    while True:
        msg, addr = server.recvfrom(1024)
        msg = msg.decode('utf-8','replace')

        print(f'Got data" {msg} " from {addr}')