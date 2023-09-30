#!/usr/bin/env python3

import socket

host = '127.0.0.1' # Standard loopback interface address (localhost)
port = 65432        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # bind() es el metodo usado para asociar el socket con una interfaz de red y un número de puerto especifico
    s.bind((host, port))
    # listen() permite que un servidor accepte conexiones, el servidor está en modo 'escucha'
    s.listen(5) # Especifica que con el backlog, el número de conexiones no aceptadas que el sistema permitirá antes de rechazar nuevas conexiones
    # accept() métodoque bloquea la ejecución y espera una nueva conexión entrante, cuando el cliente se conecta, devuelve un nueevo objeto de socket que representa la conexión y una tupla que contiene
    # la dirección del cliente. La tupla contendrá (host, puerto) conexiones IPv4 o (host, puerto, flowinfo, scopeid) IPv6. 
    conn, addr = s.accept()
    print(f"Connected by {addr}")
    with conn:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            conn.sendall(data)